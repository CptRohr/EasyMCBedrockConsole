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

#include "addonregistry.h"
#include "database/databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>

AddonRegistry::AddonRegistry(QObject* parent)
    : QObject(parent)
{
}

int AddonRegistry::registerPack(const PackManifest& manifest, const QString& installPath)
{
    if (!manifest.isValid()) {
        m_lastError = "Cannot register invalid manifest";
        qWarning() << m_lastError;
        emit error(m_lastError);
        return -1;
    }

    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        qWarning() << m_lastError;
        emit error(m_lastError);
        return -1;
    }

    QSqlQuery query(dbMgr.database());

    // Check if pack already exists
    query.prepare("SELECT id FROM packs WHERE uuid = ?");
    query.addBindValue(manifest.uuid());

    if (!query.exec()) {
        m_lastError = QString("Failed to check existing pack: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        emit error(m_lastError);
        return -1;
    }

    int packId = -1;
    if (query.next()) {
        // Pack exists, update it
        packId = query.value(0).toInt();
        query.prepare("UPDATE packs SET name = ?, version_major = ?, version_minor = ?, "
                     "version_patch = ?, pack_type = ?, description = ?, author = ?, "
                     "install_path = ?, min_engine_major = ?, min_engine_minor = ?, "
                     "min_engine_patch = ?, is_enabled = 1 WHERE id = ?");
    } else {
        // New pack, insert it
        query.prepare("INSERT INTO packs (uuid, name, version_major, version_minor, "
                     "version_patch, pack_type, description, author, install_path, "
                     "min_engine_major, min_engine_minor, min_engine_patch, sort_order) "
                     "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, "
                     "(SELECT COALESCE(MAX(sort_order), 0) + 1 FROM packs))");
        query.addBindValue(manifest.uuid());
    }

    query.addBindValue(manifest.name());
    query.addBindValue(manifest.versionMajor());
    query.addBindValue(manifest.versionMinor());
    query.addBindValue(manifest.versionPatch());
    query.addBindValue(manifest.typeString());
    query.addBindValue(manifest.description());
    query.addBindValue(manifest.author());
    query.addBindValue(installPath);
    query.addBindValue(manifest.minEngineMajor());
    query.addBindValue(manifest.minEngineMinor());
    query.addBindValue(manifest.minEnginePatch());

    if (packId != -1) {
        // UPDATE query: add id
        query.addBindValue(packId);
    }

    if (!query.exec()) {
        m_lastError = QString("Failed to register pack: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        emit error(m_lastError);
        return -1;
    }

    if (packId == -1) {
        // Get the ID of the newly inserted pack
        packId = query.lastInsertId().toInt();
    }

    // Clear existing dependencies for this pack
    query.prepare("DELETE FROM pack_dependencies WHERE pack_id = ?");
    query.addBindValue(packId);
    if (!query.exec()) {
        qWarning() << "Failed to clear existing dependencies:" << query.lastError().text();
    }

    // Register dependencies
    for (const auto& dep : manifest.dependencies()) {
        if (!registerDependency(manifest.uuid(), dep.uuid, dep.versionMajor, dep.versionMinor, dep.versionPatch)) {
            qWarning() << "Failed to register dependency" << dep.uuid << "for pack" << manifest.uuid();
        }
    }

    qDebug() << "Registered pack" << manifest.uuid() << "(" << manifest.name() << ") with ID" << packId;
    emit packRegistered(manifest.uuid(), manifest.name());

    return packId;
}

PackInfo AddonRegistry::getPack(const QString& uuid)
{
    PackInfo info;

    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return info;
    }

    QSqlQuery query(dbMgr.database());
    query.prepare("SELECT id, uuid, name, description, author, version_major, version_minor, "
                 "version_patch, pack_type, install_path, is_enabled, installed_at, "
                 "min_engine_major, min_engine_minor, min_engine_patch, sort_order FROM packs WHERE uuid = ?");
    query.addBindValue(uuid);

    if (!query.exec()) {
        m_lastError = QString("Failed to query pack: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        return info;
    }

    if (query.next()) {
        info.id = query.value(0).toInt();
        info.uuid = query.value(1).toString();
        info.name = query.value(2).toString();
        info.description = query.value(3).toString();
        info.author = query.value(4).toString();
        info.versionMajor = query.value(5).toInt();
        info.versionMinor = query.value(6).toInt();
        info.versionPatch = query.value(7).toInt();
        info.packType = query.value(8).toString();
        info.installPath = query.value(9).toString();
        info.isEnabled = query.value(10).toInt() != 0;
        info.installedAt = query.value(11).toString();
        info.minEngineMajor = query.value(12).toInt();
        info.minEngineMinor = query.value(13).toInt();
        info.minEnginePatch = query.value(14).toInt();
        info.sortOrder = query.value(15).toInt();
    }

    return info;
}

QVector<PackInfo> AddonRegistry::getAllPacks(const QString& packType)
{
    QVector<PackInfo> packs;

    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return packs;
    }

    QSqlQuery query(dbMgr.database());

    if (packType.isEmpty()) {
        query.prepare("SELECT id, uuid, name, description, author, version_major, version_minor, "
                     "version_patch, pack_type, install_path, is_enabled, installed_at, "
                     "min_engine_major, min_engine_minor, min_engine_patch, sort_order FROM packs ORDER BY sort_order ASC, name ASC");
    } else {
        query.prepare("SELECT id, uuid, name, description, author, version_major, version_minor, "
                     "version_patch, pack_type, install_path, is_enabled, installed_at, "
                     "min_engine_major, min_engine_minor, min_engine_patch, sort_order FROM packs WHERE pack_type = ? ORDER BY sort_order ASC, name ASC");
        query.addBindValue(packType);
    }

    if (!query.exec()) {
        m_lastError = QString("Failed to query packs: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        return packs;
    }

    while (query.next()) {
        PackInfo info;
        info.id = query.value(0).toInt();
        info.uuid = query.value(1).toString();
        info.name = query.value(2).toString();
        info.description = query.value(3).toString();
        info.author = query.value(4).toString();
        info.versionMajor = query.value(5).toInt();
        info.versionMinor = query.value(6).toInt();
        info.versionPatch = query.value(7).toInt();
        info.packType = query.value(8).toString();
        info.installPath = query.value(9).toString();
        info.isEnabled = query.value(10).toInt() != 0;
        info.installedAt = query.value(11).toString();
        info.minEngineMajor = query.value(12).toInt();
        info.minEngineMinor = query.value(13).toInt();
        info.minEnginePatch = query.value(14).toInt();
        info.sortOrder = query.value(15).toInt();
        packs.append(info);
    }

    return packs;
}

bool AddonRegistry::packExists(const QString& uuid)
{
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        return false;
    }

    QSqlQuery query(dbMgr.database());
    query.prepare("SELECT COUNT(*) FROM packs WHERE uuid = ?");
    query.addBindValue(uuid);

    if (!query.exec()) {
        qWarning() << "Failed to check pack existence:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
}

bool AddonRegistry::setPackEnabled(const QString& uuid, bool enabled)
{
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return false;
    }

    QSqlQuery query(dbMgr.database());
    query.prepare("UPDATE packs SET is_enabled = ? WHERE uuid = ?");
    query.addBindValue(enabled ? 1 : 0);
    query.addBindValue(uuid);

    if (!query.exec()) {
        m_lastError = QString("Failed to update pack status: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool AddonRegistry::uninstallPack(const QString& uuid, bool deleteFiles)
{
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return false;
    }

    PackInfo info = getPack(uuid);
    if (info.id == -1) {
        m_lastError = "Pack not found";
        return false;
    }

    QSqlQuery query(dbMgr.database());

    // Delete dependencies
    query.prepare("DELETE FROM pack_dependencies WHERE pack_id = ?");
    query.addBindValue(info.id);
    if (!query.exec()) {
        qWarning() << "Failed to delete dependencies:" << query.lastError().text();
    }

    // Delete pack
    query.prepare("DELETE FROM packs WHERE id = ?");
    query.addBindValue(info.id);
    if (!query.exec()) {
        m_lastError = QString("Failed to uninstall pack: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        return false;
    }

    // Delete files if requested
    if (deleteFiles && !info.installPath.isEmpty()) {
        QDir packDir(info.installPath);
        if (packDir.exists()) {
            if (packDir.removeRecursively()) {
                qDebug() << "Deleted pack files from" << info.installPath;
            } else {
                qWarning() << "Failed to delete pack files from" << info.installPath;
            }
        }
    }

    qDebug() << "Uninstalled pack" << uuid;
    emit packUninstalled(uuid);

    return true;
}

bool AddonRegistry::registerDependency(const QString& packUuid, const QString& dependencyUuid,
                                       int depVersionMajor, int depVersionMinor, int depVersionPatch)
{
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return false;
    }

    PackInfo packInfo = getPack(packUuid);
    if (packInfo.id == -1) {
        m_lastError = QString("Pack not found: %1").arg(packUuid);
        return false;
    }

    QSqlQuery query(dbMgr.database());
    query.prepare("INSERT INTO pack_dependencies (pack_id, dep_uuid, dep_version_major, "
                 "dep_version_minor, dep_version_patch) VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(packInfo.id);
    query.addBindValue(dependencyUuid);
    query.addBindValue(depVersionMajor);
    query.addBindValue(depVersionMinor);
    query.addBindValue(depVersionPatch);

    if (!query.exec()) {
        m_lastError = QString("Failed to register dependency: %1").arg(query.lastError().text());
        qWarning() << m_lastError;
        return false;
    }

    return true;
}

QVector<PackDependency> AddonRegistry::getDependencies(const QString& packUuid)
{
    QVector<PackDependency> dependencies;

    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        return dependencies;
    }

    PackInfo packInfo = getPack(packUuid);
    if (packInfo.id == -1) {
        return dependencies;
    }

    QSqlQuery query(dbMgr.database());
    query.prepare("SELECT dep_uuid, dep_version_major, dep_version_minor, dep_version_patch "
                 "FROM pack_dependencies WHERE pack_id = ?");
    query.addBindValue(packInfo.id);

    if (!query.exec()) {
        qWarning() << "Failed to query dependencies:" << query.lastError().text();
        return dependencies;
    }

    while (query.next()) {
        PackDependency dep;
        dep.uuid = query.value(0).toString();
        dep.versionMajor = query.value(1).toInt();
        dep.versionMinor = query.value(2).toInt();
        dep.versionPatch = query.value(3).toInt();
        dependencies.append(dep);
    }

    return dependencies;
}

bool AddonRegistry::swapPacksOrder(const QString& uuid1, const QString& uuid2)
{
    DatabaseManager& dbMgr = DatabaseManager::instance();
    if (!dbMgr.isReady()) {
        m_lastError = "Database not ready";
        return false;
    }

    QSqlQuery query(dbMgr.database());

    int order1 = -1;
    int order2 = -1;

    query.prepare("SELECT sort_order FROM packs WHERE uuid = ?");
    query.addBindValue(uuid1);
    if (query.exec() && query.next()) {
        order1 = query.value(0).toInt();
    }

    query.prepare("SELECT sort_order FROM packs WHERE uuid = ?");
    query.addBindValue(uuid2);
    if (query.exec() && query.next()) {
        order2 = query.value(0).toInt();
    }

    // If both have the same sort order (e.g. default 0), assign sequential orders first
    if (order1 == order2) {
        QVector<PackInfo> all = getAllPacks();
        for (int i = 0; i < all.size(); ++i) {
            query.prepare("UPDATE packs SET sort_order = ? WHERE uuid = ?");
            query.addBindValue(i);
            query.addBindValue(all[i].uuid);
            query.exec();

            if (all[i].uuid == uuid1) order1 = i;
            if (all[i].uuid == uuid2) order2 = i;
        }
    }

    // Swap the orders
    query.prepare("UPDATE packs SET sort_order = ? WHERE uuid = ?");
    query.addBindValue(order2);
    query.addBindValue(uuid1);
    bool ok1 = query.exec();

    query.prepare("UPDATE packs SET sort_order = ? WHERE uuid = ?");
    query.addBindValue(order1);
    query.addBindValue(uuid2);
    bool ok2 = query.exec();

    if (!ok1 || !ok2) {
        m_lastError = "Failed to update swap orders in database";
        return false;
    }

    return true;
}
