/***
 *
 * This file is part of Minecraft Bedrock Server Console software.
 *
 * It is licenced under the GNU GPL Version 3.
 *
 * A copy of this can be found in the LICENCE file
 *
 * (c) Ian Clark
 *
 **
*/

#include "addoninstaller.h"
#include "archiveextractor.h"
#include "addonregistry.h"
#include <QDir>
#include <QDebug>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

// BulkInstallResult implementation
int BulkInstallResult::successCount() const
{
    int count = 0;
    for (const auto& result : results) {
        if (result.status == InstallResult::Success) {
            count++;
        }
    }
    return count;
}

int BulkInstallResult::failureCount() const
{
    int count = 0;
    for (const auto& result : results) {
        if (result.status == InstallResult::ValidationFailed ||
            result.status == InstallResult::InstallationFailed ||
            result.status == InstallResult::Cancelled) {
            count++;
        }
    }
    return count;
}



// AddonInstaller implementation
AddonInstaller::AddonInstaller(QObject* parent)
    : QObject(parent)
    , m_extractor(new ArchiveExtractor(this))
    , m_registry(new AddonRegistry(this))
{
    // Connect extractor signals
    connect(m_extractor, &ArchiveExtractor::progressUpdated,
            this, [this](int progress) {
        emit progressUpdated("Extracting archive...", progress);
    });

    connect(m_extractor, &ArchiveExtractor::error,
            this, [this](const QString& errorMsg) {
        m_lastError = errorMsg;
        emit error(errorMsg);
    });

    // Connect registry signals
    connect(m_registry, &AddonRegistry::packRegistered,
            this, &AddonInstaller::packInstalled);

    connect(m_registry, &AddonRegistry::error,
            this, [this](const QString& errorMsg) {
        m_lastError = errorMsg;
        emit error(errorMsg);
    });
}

AddonInstaller::~AddonInstaller()
{
}

BulkInstallResult AddonInstaller::installFromPath(const QString& filePath, const QString& serverRootPath)
{
    BulkInstallResult bulkResult;

    emit progressUpdated("Detecting archive type...", 0);

    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists()) {
        m_lastError = "File not found: " + filePath;
        qCritical() << m_lastError;
        emit error(m_lastError);

        InstallResult result;
        result.status = InstallResult::InstallationFailed;
        result.message = m_lastError;
        bulkResult.results.append(result);
        return bulkResult;
    }

    // If it's a directory, install directly
    if (fileInfo.isDir()) {
        return installFromExtractedDirectory(filePath, serverRootPath);
    }

    // Extract archive
    emit progressUpdated("Extracting archive...", 10);
    QString extractedPath = m_extractor->extract(filePath);

    if (extractedPath.isEmpty()) {
        m_lastError = "Failed to extract archive: " + m_extractor->lastError();
        qCritical() << m_lastError;
        emit error(m_lastError);

        InstallResult result;
        result.status = InstallResult::InstallationFailed;
        result.message = m_lastError;
        bulkResult.results.append(result);
        return bulkResult;
    }

    // Install from extracted directory
    return installFromExtractedDirectory(extractedPath, serverRootPath);
}

BulkInstallResult AddonInstaller::installFromExtractedDirectory(const QString& extractedDirPath, const QString& serverRootPath)
{
    BulkInstallResult bulkResult;

    emit progressUpdated("Discovering packs...", 20);

    // Find all manifest.json files
    QStringList manifestFiles = findManifestFiles(extractedDirPath);

    if (manifestFiles.isEmpty()) {
        m_lastError = "No manifest.json files found in extracted archive";
        qWarning() << m_lastError;
        emit error(m_lastError);

        InstallResult result;
        result.status = InstallResult::InstallationFailed;
        result.message = m_lastError;
        bulkResult.results.append(result);
        return bulkResult;
    }

    qDebug() << "Found" << manifestFiles.size() << "pack(s) to install";

    // Process each pack
    int totalFiles = manifestFiles.size();
    for (int i = 0; i < manifestFiles.size(); ++i) {
        QString manifestPath = manifestFiles.at(i);
        QString packDir = QFileInfo(manifestPath).dir().absolutePath();

        emit progressUpdated(QString("Processing pack %1/%2...").arg(i + 1).arg(totalFiles),
                           20 + (i * 60) / totalFiles);

        // Parse manifest
        PackManifest manifest = PackManifest::parseFromDirectory(packDir);

        InstallResult result;
        result.packName = manifest.name();
        result.uuid = manifest.uuid();

        // Validate manifest
        if (!manifest.isValid()) {
            result.status = InstallResult::ValidationFailed;
            result.message = manifest.errorMessage();
            result.validationResult.severity = ValidationResult::Error;
            result.validationResult.message = manifest.errorMessage();
            qWarning() << "Manifest validation failed for" << packDir << ":" << manifest.errorMessage();
            bulkResult.results.append(result);
            continue;
        }

        // Validate pack
        ValidationResult validation = AddonValidator::validate(manifest);
        result.validationResult = validation;

        // Treat warnings as non‑fatal; only errors block installation
        if (validation.severity == ValidationResult::Error) {
            result.status = InstallResult::ValidationFailed;
            result.message = validation.message;
            qWarning() << "Pack validation error (blocking):" << validation.message;
            bulkResult.results.append(result);
            continue;
        } else if (validation.severity == ValidationResult::Warning) {
            qInfo() << "Pack validation warning (non‑blocking):" << validation.message;
        }

        // Check if pack already installed
        if (m_registry->packExists(manifest.uuid())) {
            QString existingVersion = AddonValidator::getExistingPackVersion(manifest.uuid());
            result.status = InstallResult::AlreadyInstalled;
            result.message = QString("Pack version %1 already installed").arg(existingVersion);
            qDebug() << "Pack already installed:" << manifest.uuid();
            bulkResult.results.append(result);
            continue;
        }

        // Copy pack to server
        QString installPath = copyPackToServer(packDir, serverRootPath, manifest);
        if (installPath.isEmpty()) {
            result.status = InstallResult::InstallationFailed;
            result.message = "Failed to copy pack to server";
            qWarning() << "Failed to copy pack to server for" << manifest.uuid();
            bulkResult.results.append(result);
            continue;
        }

        // Register in database
        int packId = m_registry->registerPack(manifest, installPath);
        if (packId == -1) {
            result.status = InstallResult::InstallationFailed;
            result.message = m_registry->lastError();
            qWarning() << "Failed to register pack in database:" << result.message;
            bulkResult.results.append(result);
            continue;
        }

        // Success!
        result.status = InstallResult::Success;
        result.message = QString("Successfully installed %1 v%2")
                         .arg(manifest.name(), manifest.versionString());
        qDebug() << "Successfully installed pack" << manifest.uuid();
        bulkResult.results.append(result);
    }

    emit progressUpdated("Installation complete", 100);

    qDebug() << "Installation summary: " << bulkResult.successCount() << "succeeded,"
             << bulkResult.failureCount() << "failed";

    emit installationCompleted(bulkResult);
    return bulkResult;
}



QStringList AddonInstaller::findManifestFiles(const QString& rootDir)
{
    QStringList manifestFiles;

    QDirIterator it(rootDir, QStringList() << "manifest.json", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        manifestFiles.append(it.next());
    }

    return manifestFiles;
}

QString AddonInstaller::copyPackToServer(const QString& sourceDirPath, const QString& serverRootPath, const PackManifest& manifest)
{
    QString installDir = getPackInstallDirectory(serverRootPath, manifest.typeString());

    if (installDir.isEmpty()) {
        m_lastError = "Unknown pack type: " + manifest.typeString();
        qCritical() << m_lastError;
        return "";
    }

    // Create target directory using UUID as the folder name
    QString packFolderName = manifest.uuid();
    QString targetPath = QDir(installDir).filePath(packFolderName);

    // Create the directory if it doesn't exist
    QDir targetDir(targetPath);
    if (!targetDir.exists() && !targetDir.mkpath(".")) {
        m_lastError = "Failed to create directory: " + targetPath;
        qCritical() << m_lastError;
        return "";
    }

    // Copy the pack files
    QDir sourceDir(sourceDirPath);
    QDirIterator it(sourceDirPath, QDir::AllEntries | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString sourceFilePath = it.next();
        QString relativePath = QDir(sourceDirPath).relativeFilePath(sourceFilePath);
        QString targetFilePath = QDir(targetPath).filePath(relativePath);

        if (it.fileInfo().isDir()) {
            if (!QDir().mkpath(targetFilePath)) {
                m_lastError = "Failed to create directory: " + targetFilePath;
                qCritical() << m_lastError;
                return "";
            }
        } else {
            if (QFile::exists(targetFilePath)) {
                QFile::remove(targetFilePath);
            }
            if (!QFile::copy(sourceFilePath, targetFilePath)) {
                m_lastError = "Failed to copy file: " + sourceFilePath + " to " + targetFilePath;
                qCritical() << m_lastError;
                return "";
            }
        }
    }

    qDebug() << "Copied pack to" << targetPath;
    return targetPath;
}

QString AddonInstaller::getPackInstallDirectory(const QString& serverRootPath, const QString& packType)
{
    if (packType == "behavior") {
        return QDir(serverRootPath).filePath("behavior_packs");
    } else if (packType == "resource") {
        return QDir(serverRootPath).filePath("resource_packs");
    } else if (packType == "skin") {
        return QDir(serverRootPath).filePath("skin_packs");
    }

    return "";
}
