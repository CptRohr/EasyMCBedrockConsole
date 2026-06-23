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

#include "addonmanager.h"
#include "database/databasemanager.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

AddonManager::AddonManager(const QString& serverRootPath, QObject* parent)
    : QObject(parent)
    , m_serverRootPath(serverRootPath)
    , m_installer(new AddonInstaller(this))
    , m_registry(new AddonRegistry(this))
    , m_isReady(false)
{
    // Connect installer signals
    connect(m_installer, &AddonInstaller::progressUpdated,
            this, &AddonManager::installationProgress);

    connect(m_installer, &AddonInstaller::packInstalled,
            this, &AddonManager::packInstalled);

    connect(m_installer, &AddonInstaller::installationCompleted,
            this, &AddonManager::installationCompleted);

    connect(m_installer, &AddonInstaller::error,
            this, &AddonManager::error);

    // Connect registry signals
    connect(m_registry, &AddonRegistry::packUninstalled,
            this, &AddonManager::packUninstalled);

    connect(m_registry, &AddonRegistry::error,
            this, &AddonManager::error);

    // Initialize if path provided
    if (!serverRootPath.isEmpty()) {
        initialize(serverRootPath);
    }
}

AddonManager::~AddonManager()
{
}

bool AddonManager::initialize(const QString& serverRootPath)
{
    m_serverRootPath = serverRootPath;

    // Initialize database
    DatabaseManager& dbMgr = DatabaseManager::instance(m_serverRootPath);
    if (!dbMgr.initialize(m_serverRootPath)) {
        emit error(dbMgr.lastError());
        return false;
    }

    if (!dbMgr.isReady()) {
        emit error("Database initialization failed");
        return false;
    }

    m_isReady = true;
    qDebug() << "AddonManager initialized with server path:" << m_serverRootPath;
    syncWorldPacks();
    emit initialized();
    return true;
}

bool AddonManager::isReady() const
{
    return m_isReady && DatabaseManager::instance().isReady();
}

BulkInstallResult AddonManager::installAddon(const QString& filePath)
{
    BulkInstallResult result;

    if (!isReady()) {
        emit error("AddonManager not ready");
        InstallResult failResult;
        failResult.status = InstallResult::InstallationFailed;
        failResult.message = "AddonManager not ready";
        result.results.append(failResult);
        return result;
    }

    result = m_installer->installFromPath(filePath, m_serverRootPath);
    syncWorldPacks();
    return result;
}

QVector<PackInfo> AddonManager::getInstalledPacks(const QString& packType)
{
    if (!isReady()) {
        return QVector<PackInfo>();
    }

    return m_registry->getAllPacks(packType);
}

PackInfo AddonManager::getPack(const QString& uuid)
{
    PackInfo info;

    if (!isReady()) {
        return info;
    }

    return m_registry->getPack(uuid);
}

bool AddonManager::setPackEnabled(const QString& uuid, bool enabled)
{
    if (!isReady()) {
        return false;
    }

    bool success = m_registry->setPackEnabled(uuid, enabled);
    if (success) {
        syncWorldPacks();
    }
    return success;
}

bool AddonManager::uninstallPack(const QString& uuid, bool deleteFiles)
{
    if (!isReady()) {
        return false;
    }

    bool success = m_registry->uninstallPack(uuid, deleteFiles);
    if (success) {
        syncWorldPacks();
    }
    return success;
}

bool AddonManager::swapPacksOrder(const QString& uuid1, const QString& uuid2)
{
    if (!isReady()) {
        return false;
    }

    bool success = m_registry->swapPacksOrder(uuid1, uuid2);
    if (success) {
        syncWorldPacks();
    }
    return success;
}

QString AddonManager::lastError() const
{
    if (!m_installer->lastError().isEmpty()) {
        return m_installer->lastError();
    }

    if (!m_registry->lastError().isEmpty()) {
        return m_registry->lastError();
    }

    return DatabaseManager::instance().lastError();
}

void AddonManager::syncWorldPacks()
{
    if (!isReady()) return;

    // 1. Read level-name from server.properties
    QString levelName = "Bedrock Level"; // default fallback
    QFile configFile(QDir(m_serverRootPath).filePath("server.properties"));
    if (configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&configFile);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.startsWith('#')) continue;
            int eqIdx = line.indexOf('=');
            if (eqIdx > 0) {
                QString key = line.left(eqIdx).trimmed();
                QString value = line.mid(eqIdx + 1).trimmed();
                if (key == "level-name") {
                    levelName = value;
                    break;
                }
            }
        }
        configFile.close();
    }

    if (levelName.isEmpty()) {
        levelName = "Bedrock Level";
    }

    // 2. Prepare paths
    QDir worldDir(QDir(m_serverRootPath).filePath("worlds/" + levelName));
    QString behaviorPacksJsonPath = worldDir.filePath("world_behavior_packs.json");
    QString resourcePacksJsonPath = worldDir.filePath("world_resource_packs.json");

    // 3. Get all packs and partition them by type
    QVector<PackInfo> allPacks = m_registry->getAllPacks();
    QJsonArray behaviorPacksJson;
    QJsonArray resourcePacksJson;

    for (const auto& pack : allPacks) {
        if (!pack.isEnabled) continue;

        QJsonObject packObj;
        packObj["pack_id"] = pack.uuid;
        QJsonArray versionArray;
        versionArray.append(pack.versionMajor);
        versionArray.append(pack.versionMinor);
        versionArray.append(pack.versionPatch);
        packObj["version"] = versionArray;

        if (pack.packType == "behavior") {
            behaviorPacksJson.append(packObj);
        } else if (pack.packType == "resource") {
            resourcePacksJson.append(packObj);
        }
    }

    // 4. Create worlds directory if not exists
    if (!worldDir.exists()) {
        if (!worldDir.mkpath(".")) {
            qWarning() << "Failed to create world directory for sync:" << worldDir.absolutePath();
            return;
        }
    }

    // 5. Write behavior packs json
    QFile bpFile(behaviorPacksJsonPath);
    if (bpFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument doc(behaviorPacksJson);
        bpFile.write(doc.toJson(QJsonDocument::Indented));
        bpFile.close();
        qDebug() << "Synced behavior packs to" << behaviorPacksJsonPath;
    } else {
        qWarning() << "Failed to open world_behavior_packs.json for writing:" << bpFile.errorString();
    }

    // 6. Write resource packs json
    QFile rpFile(resourcePacksJsonPath);
    if (rpFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QJsonDocument doc(resourcePacksJson);
        rpFile.write(doc.toJson(QJsonDocument::Indented));
        rpFile.close();
        qDebug() << "Synced resource packs to" << resourcePacksJsonPath;
    } else {
        qWarning() << "Failed to open world_resource_packs.json for writing:" << rpFile.errorString();
    }
}
