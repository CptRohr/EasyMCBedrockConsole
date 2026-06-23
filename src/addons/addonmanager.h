#ifndef ADDONMANAGER_H
#define ADDONMANAGER_H

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

#include <QObject>
#include <QString>
#include "addoninstaller.h"
#include "addonregistry.h"

/**
 * @class AddonManager
 * @brief Top-level service for managing Bedrock addon packs.
 *
 * Coordinates all addon-related operations including installation, validation,
 * registry management, and database interactions. Provides a clean public API
 * for the UI layer.
 */
class AddonManager : public QObject
{
    Q_OBJECT

public:
    explicit AddonManager(const QString& serverRootPath = "", QObject* parent = nullptr);
    ~AddonManager();

    /**
     * @brief Initialize the addon manager with a server root path.
     * @param serverRootPath Path to the Bedrock server root directory.
     * @return True if initialization succeeded; false otherwise.
     */
    bool initialize(const QString& serverRootPath);

    /**
     * @brief Check if addon manager is ready for use.
     * @return True if initialized and database is ready.
     */
    bool isReady() const;

    /**
     * @brief Install addon from a file or directory.
     * @param filePath Path to .mcaddon, .mcpack, .zip, or directory.
     * @return Result(s) of the installation.
     */
    BulkInstallResult installAddon(const QString& filePath);

    /**
     * @brief Get all installed packs, optionally filtered by type.
     * @param packType Filter by type ("behavior", "resource", "skin"), or empty for all.
     * @return List of installed packs.
     */
    QVector<PackInfo> getInstalledPacks(const QString& packType = "");

    /**
     * @brief Get a specific pack by UUID.
     * @param uuid The pack UUID.
     * @return Pack information, or invalid PackInfo if not found.
     */
    PackInfo getPack(const QString& uuid);

    /**
     * @brief Enable or disable a pack.
     * @param uuid The pack UUID.
     * @param enabled New enabled state.
     * @return True if update succeeded; false otherwise.
     */
    bool setPackEnabled(const QString& uuid, bool enabled);

    /**
     * @brief Uninstall a pack.
     * @param uuid The pack UUID.
     * @param deleteFiles If true, also delete files from disk.
     * @return True if uninstall succeeded; false otherwise.
     */
    bool uninstallPack(const QString& uuid, bool deleteFiles = true);

    /**
     * @brief Swap the sort orders of two packs.
     * @param uuid1 First pack UUID.
     * @param uuid2 Second pack UUID.
     * @return True if swap succeeded; false otherwise.
     */
    bool swapPacksOrder(const QString& uuid1, const QString& uuid2);

    /**
     * @brief Get the server root path.
     * @return Path to the Bedrock server root.
     */
    QString serverRootPath() const { return m_serverRootPath; }

    /**
     * @brief Get the last error message.
     * @return Detailed error description.
     */
    QString lastError() const;

signals:
    /**
     * @brief Emitted when addon manager is initialized.
     */
    void initialized();

    /**
     * @brief Emitted during installation progress.
     * @param currentFile Name of current file being processed.
     * @param progressPercent Progress 0-100.
     */
    void installationProgress(const QString& currentFile, int progressPercent);

    /**
     * @brief Emitted when a pack is successfully installed.
     * @param uuid UUID of the installed pack.
     * @param packName Name of the installed pack.
     */
    void packInstalled(const QString& uuid, const QString& packName);

    /**
     * @brief Emitted when installation completes.
     * @param result Summary of results.
     */
    void installationCompleted(const BulkInstallResult& result);

    /**
     * @brief Emitted when a pack is uninstalled.
     * @param uuid UUID of the uninstalled pack.
     */
    void packUninstalled(const QString& uuid);

    /**
     * @brief Emitted when an error occurs.
     * @param errorMessage Description of the error.
     */
    void error(const QString& errorMessage);

private:
    void syncWorldPacks();

    QString m_serverRootPath;
    AddonInstaller* m_installer;
    AddonRegistry* m_registry;
    bool m_isReady;
};

#endif // ADDONMANAGER_H
