#ifndef ADDONINSTALLER_H
#define ADDONINSTALLER_H

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

#include "packmanifest.h"
#include "addonvalidator.h"
#include <QString>
#include <QObject>
#include <QVector>

class ArchiveExtractor;
class AddonRegistry;

/**
 * @struct InstallResult
 * @brief Result of a single pack installation.
 */
struct InstallResult
{
    enum Status {
        Success,
        AlreadyInstalled,
        ValidationFailed,
        InstallationFailed,
        Cancelled
    };

    Status status = InstallationFailed;
    QString uuid;
    QString packName;
    QString message;
    ValidationResult validationResult;
};

/**
 * @struct BulkInstallResult
 * @brief Result of installing multiple packs (e.g., from a .mcaddon file).
 */
struct BulkInstallResult
{
    QVector<InstallResult> results;
    int successCount() const;
    int failureCount() const;
    bool allSuccessful() const { return failureCount() == 0; }
};

/**
 * @class AddonInstaller
 * @brief Orchestrates the addon installation pipeline.
 *
 * Implements all stages of installation:
 * 1. Detection (archive type)
 * 2. Extraction (to temporary directory)
 * 3. Pack discovery (find manifest.json files)
 * 4. Manifest parsing
 * 5. Validation
 * 6. File placement (copy to server directory)
 * 7. Registry update (record in database)
 * 8. Model notification (update UI)
 */
class AddonInstaller : public QObject
{
    Q_OBJECT

public:
    explicit AddonInstaller(QObject* parent = nullptr);
    ~AddonInstaller();

    /**
     * @brief Install addon(s) from a file (archive or directory).
     * @param filePath Path to .mcaddon, .mcpack, .zip, or directory.
     * @param serverRootPath Path to the Bedrock server root directory.
     * @return Result(s) of the installation attempt.
     */
    BulkInstallResult installFromPath(const QString& filePath, const QString& serverRootPath);

    /**
     * @brief Install from an already-extracted directory.
     * @param extractedDirPath Path containing manifest.json files.
     * @param serverRootPath Path to the Bedrock server root directory.
     * @return Result(s) of the installation attempt.
     */
    BulkInstallResult installFromExtractedDirectory(const QString& extractedDirPath, const QString& serverRootPath);

    /**
     * @brief Get the last error message.
     * @return Detailed error description.
     */
    QString lastError() const { return m_lastError; }

signals:
    /**
     * @brief Emitted periodically during installation.
     * @param currentFile Name of the file being processed.
     * @param progressPercent Progress from 0 to 100.
     */
    void progressUpdated(const QString& currentFile, int progressPercent);

    /**
     * @brief Emitted when a pack is successfully installed.
     * @param uuid UUID of the installed pack.
     * @param packName Name of the installed pack.
     */
    void packInstalled(const QString& uuid, const QString& packName);

    /**
     * @brief Emitted when installation completes.
     * @param result Summary of the installation result.
     */
    void installationCompleted(const BulkInstallResult& result);

    /**
     * @brief Emitted when an error occurs.
     * @param errorMessage Description of the error.
     */
    void error(const QString& errorMessage);

private:
    /**
     * @brief Find all manifest.json files in a directory tree.
     * @param rootDir Root directory to search.
     * @return List of absolute paths to manifest.json files.
     */
    QStringList findManifestFiles(const QString& rootDir);

    /**
     * @brief Copy a pack directory to the appropriate location in the server.
     * @param sourceDirPath Path to the pack directory to copy.
     * @param serverRootPath Path to the server root.
     * @param manifest The parsed manifest of the pack.
     * @return Absolute path to the installed pack, or empty string on failure.
     */
    QString copyPackToServer(const QString& sourceDirPath, const QString& serverRootPath, const PackManifest& manifest);

    /**
     * @brief Get the installation directory for a pack type.
     * @param serverRootPath Path to the server root.
     * @param packType The pack type (behavior, resource, skin).
     * @return Path to the appropriate directory.
     */
    QString getPackInstallDirectory(const QString& serverRootPath, const QString& packType);

    ArchiveExtractor* m_extractor;
    AddonRegistry* m_registry;
    QString m_lastError;
};

#endif // ADDONINSTALLER_H
