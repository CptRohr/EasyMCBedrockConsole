#ifndef ADDONREGISTRY_H
#define ADDONREGISTRY_H

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
#include <QString>
#include <QVector>
#include <QObject>

/**
 * @struct PackInfo
 * @brief Database representation of an installed pack.
 */
struct PackInfo
{
    int id = -1;
    QString uuid;
    QString name;
    QString description;
    QString author;
    int versionMajor = 0;
    int versionMinor = 0;
    int versionPatch = 0;
    QString packType; // "behavior", "resource", "skin"
    QString installPath;
    bool isEnabled = true;
    QString installedAt;
    int minEngineMajor = 1;
    int minEngineMinor = 20;
    int minEnginePatch = 0;
    int sortOrder = 0;

    QString versionString() const {
        return QString("%1.%2.%3").arg(versionMajor).arg(versionMinor).arg(versionPatch);
    }
};

/**
 * @class AddonRegistry
 * @brief Manages CRUD operations for installed addons in the database.
 *
 * Provides methods to register, retrieve, update, and remove addon packs
 * from the SQLite registry.
 */
class AddonRegistry : public QObject
{
    Q_OBJECT

public:
    explicit AddonRegistry(QObject* parent = nullptr);

    /**
     * @brief Register a newly installed pack in the database.
     * @param manifest The parsed manifest of the pack.
     * @param installPath Absolute path where the pack is installed.
     * @return ID of the inserted pack, or -1 on failure.
     */
    int registerPack(const PackManifest& manifest, const QString& installPath);

    /**
     * @brief Get a pack by its UUID.
     * @param uuid The pack UUID.
     * @return PackInfo if found; otherwise PackInfo with id=-1.
     */
    PackInfo getPack(const QString& uuid);

    /**
     * @brief Get all installed packs, optionally filtered by type.
     * @param packType Filter by type ("behavior", "resource", "skin"), or empty for all.
     * @return List of all packs matching the filter.
     */
    QVector<PackInfo> getAllPacks(const QString& packType = "");

    /**
     * @brief Check if a pack UUID is already registered.
     * @param uuid The UUID to check.
     * @return True if pack exists; false otherwise.
     */
    bool packExists(const QString& uuid);

    /**
     * @brief Update a pack's enabled status.
     * @param uuid The pack UUID.
     * @param enabled New enabled state.
     * @return True if update succeeded; false otherwise.
     */
    bool setPackEnabled(const QString& uuid, bool enabled);

    /**
     * @brief Uninstall a pack (remove from registry and optionally from disk).
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
     * @brief Register a dependency between two packs.
     * @param packUuid UUID of the pack with the dependency.
     * @param dependencyUuid UUID of the dependency pack.
     * @param depVersionMajor Dependency major version.
     * @param depVersionMinor Dependency minor version.
     * @param depVersionPatch Dependency patch version.
     * @return True if registration succeeded; false otherwise.
     */
    bool registerDependency(const QString& packUuid, const QString& dependencyUuid,
                           int depVersionMajor, int depVersionMinor, int depVersionPatch);

    /**
     * @brief Get all dependencies for a pack.
     * @param packUuid UUID of the pack.
     * @return List of dependencies.
     */
    QVector<PackDependency> getDependencies(const QString& packUuid);

    /**
     * @brief Get the last error message.
     * @return Detailed error description.
     */
    QString lastError() const { return m_lastError; }

signals:
    /**
     * @brief Emitted when a pack is successfully registered.
     * @param packUuid UUID of the registered pack.
     * @param packName Name of the registered pack.
     */
    void packRegistered(const QString& packUuid, const QString& packName);

    /**
     * @brief Emitted when a pack is uninstalled.
     * @param packUuid UUID of the uninstalled pack.
     */
    void packUninstalled(const QString& packUuid);

    /**
     * @brief Emitted when an error occurs.
     * @param errorMessage Description of the error.
     */
    void error(const QString& errorMessage);

private:
    QString m_lastError;
    QString m_databasePath;
};

#endif // ADDONREGISTRY_H
