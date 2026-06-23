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

#include "archiveextractor.h"
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

ArchiveExtractor::ArchiveExtractor(QObject* parent)
    : QObject(parent)
{
}

ArchiveExtractor::ArchiveType ArchiveExtractor::detectArchiveType(const QString& filePath)
{
    QFileInfo fileInfo(filePath);
    QString suffix = fileInfo.suffix().toLower();

    if (suffix == "mcaddon") {
        return McAddon;
    } else if (suffix == "mcpack") {
        return McPack;
    } else if (suffix == "zip") {
        return ZipFile;
    }

    return Unknown;
}

QString ArchiveExtractor::extract(const QString& archiveFilePath)
{
    if (!QFile::exists(archiveFilePath)) {
        m_lastError = "Archive file not found: " + archiveFilePath;
        qCritical() << m_lastError;
        emit error(m_lastError);
        return "";
    }

    ArchiveType type = detectArchiveType(archiveFilePath);

    if (type == Unknown) {
        m_lastError = "Unknown archive type: " + archiveFilePath;
        qWarning() << m_lastError;
        emit error(m_lastError);
        return "";
    }

    qDebug() << "Extracting" << (type == McAddon ? ".mcaddon" : type == McPack ? ".mcpack" : ".zip")
             << "archive:" << archiveFilePath;

    // Create temporary directory
    if (!m_tempDir.isValid()) {
        m_lastError = "Failed to create temporary directory";
        qCritical() << m_lastError;
        emit error(m_lastError);
        return "";
    }

    if (!extractZip(archiveFilePath)) {
        return "";
    }

    emit progressUpdated(100);
    emit extractionCompleted();

    qDebug() << "Extraction successful to:" << m_tempDir.path();
    return m_tempDir.path();
}

bool ArchiveExtractor::extractZip(const QString& zipFilePath)
{
    QStringList errorDetails;

    // Try using 7-Zip first (most reliable)
    QStringList sevenZipPaths = {
        "7z",
        "7za",
        "C:\\Program Files\\7-Zip\\7z.exe",
        "C:\\Program Files (x86)\\7-Zip\\7z.exe"
    };

    for (const auto& sevenZipPath : sevenZipPaths) {
        // Skip if the executable does not exist
        if (!QFileInfo::exists(sevenZipPath) && !QFileInfo::exists(sevenZipPath + ".exe")) {
            qDebug() << "7‑Zip not found at" << sevenZipPath << "— skipping";
            continue;
        }
        QProcess process;
        QString exe = QFileInfo::exists(sevenZipPath) ? sevenZipPath : sevenZipPath + ".exe";
        qDebug() << "Attempting extraction with 7‑Zip:" << exe;
        process.start(exe, QStringList() << "x" << zipFilePath << "-o" + m_tempDir.path() << "-y");
        if (process.waitForFinished(60000)) {
            if (process.exitCode() == 0) {
                qDebug() << "Successfully extracted using 7‑Zip";
                return true;
            } else {
                QString output = QString::fromLocal8Bit(process.readAllStandardOutput()) +
                                 QString::fromLocal8Bit(process.readAllStandardError());
                qWarning() << "7‑Zip extraction failed, exit code" << process.exitCode() << "output:" << output;
                errorDetails.append(QString("7-Zip (%1) failed with exit code %2: %3")
                                    .arg(exe).arg(process.exitCode()).arg(output.trimmed()));
            }
        } else {
            qWarning() << "7‑Zip extraction timed out for" << exe;
            errorDetails.append(QString("7-Zip (%1) timed out").arg(exe));
        }
    }

    // Fallback to Windows built-in PowerShell extraction
#ifdef Q_OS_WIN
    {
        QProcess process;
        // Use escaped double-quotes so paths with spaces are handled correctly
        QString psCommand = QString(
            "Expand-Archive -Path \"%1\" -DestinationPath \"%2\" -Force"
        ).arg(
            QString(zipFilePath).replace("\\", "\\\\"),
            QString(m_tempDir.path()).replace("\\", "\\\\")
        );

        process.start("powershell.exe", QStringList() << "-NoProfile" << "-NonInteractive" << "-Command" << psCommand);
        process.waitForFinished(60000);

        if (process.exitCode() == 0) {
            qDebug() << "Successfully extracted using PowerShell";
            return true;
        } else {
            QString errorOutput = QString::fromLocal8Bit(process.readAllStandardError())
                                + QString::fromLocal8Bit(process.readAllStandardOutput());
            qWarning() << "PowerShell extraction error:" << errorOutput;
            errorDetails.append(QString("PowerShell Expand-Archive failed: %1").arg(errorOutput.trimmed()));
        }
    }
#endif

    // Fallback to system unzip command (Linux/macOS)
#ifdef Q_OS_UNIX
    QProcess process;
    process.start("unzip", QStringList() << zipFilePath << "-d" << m_tempDir.path());

    if (process.waitForFinished(30000)) {
        if (process.exitCode() == 0) {
            qDebug() << "Successfully extracted using unzip";
            return true;
        } else {
            QString output = QString::fromLocal8Bit(process.readAllStandardOutput()) +
                             QString::fromLocal8Bit(process.readAllStandardError());
            errorDetails.append(QString("unzip failed with exit code %1: %2").arg(process.exitCode()).arg(output.trimmed()));
        }
    } else {
        errorDetails.append("unzip timed out");
    }
#endif

    m_lastError = "Failed to extract archive. Details:\n" + errorDetails.join("\n");
    qCritical() << m_lastError;
    emit error(m_lastError);
    return false;
}

ArchiveExtractor::ArchiveType ArchiveExtractor::detectTypeInternal(const QString& filePath)
{
    // This is a helper method; primarily we rely on file extension
    return detectArchiveType(filePath);
}
