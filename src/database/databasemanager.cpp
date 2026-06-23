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

#include "databasemanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>

DatabaseManager* DatabaseManager::m_instance = nullptr;

DatabaseManager& DatabaseManager::instance(const QString& serverRootPath)
{
    if (!m_instance) {
        m_instance = new DatabaseManager();
    }

    if (!serverRootPath.isEmpty() && (m_instance->m_serverRootPath != serverRootPath || !m_instance->m_isReady)) {
        m_instance->initialize(serverRootPath);
    }

    return *m_instance;
}

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent)
    , m_currentSchemaVersion(0)
    , m_isReady(false)
{
}

bool DatabaseManager::initialize(const QString& serverRootPath)
{
    m_serverRootPath = serverRootPath;
    
    // Create database directory path
    QString dbDir = QDir(m_serverRootPath).filePath("bedrock_manager");
    QDir().mkpath(dbDir);
    
    m_databasePath = QDir(dbDir).filePath("addon_registry.db");
    
    // Close any existing addon_registry connection before reuse
    if (QSqlDatabase::contains("addon_registry")) {
        {
            QSqlDatabase oldDb = QSqlDatabase::database("addon_registry");
            if (oldDb.isOpen()) {
                oldDb.close();
            }
        }
        QSqlDatabase::removeDatabase("addon_registry");
    }

    // Create or open SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "addon_registry");
    db.setDatabaseName(m_databasePath);
    
    if (!db.open()) {
        m_lastError = QString("Failed to open database: %1").arg(db.lastError().text());
        qCritical() << m_lastError;
        emit error(m_lastError);
        return false;
    }
    
    m_database = db;
    
    // Initialize version tracking table
    if (!initializeVersionTable()) {
        m_lastError = "Failed to initialize version table";
        qCritical() << m_lastError;
        emit error(m_lastError);
        return false;
    }
    
    // Apply pending migrations
    if (!applyMigrations()) {
        m_lastError = "Failed to apply database migrations";
        qCritical() << m_lastError;
        emit error(m_lastError);
        return false;
    }

    // Ensure sort_order column exists in packs table for backward compatibility
    {
        QSqlQuery query(m_database);
        if (query.exec("PRAGMA table_info(packs)")) {
            bool hasSortOrder = false;
            while (query.next()) {
                if (query.value(1).toString() == "sort_order") {
                    hasSortOrder = true;
                    break;
                }
            }
            if (!hasSortOrder) {
                QSqlQuery alterQuery(m_database);
                if (alterQuery.exec("ALTER TABLE packs ADD COLUMN sort_order INTEGER DEFAULT 0")) {
                    qDebug() << "Added sort_order column to packs table";
                } else {
                    qWarning() << "Failed to add sort_order column to packs table:" << alterQuery.lastError().text();
                }
            }
        }
    }
    
    m_isReady = true;
    qDebug() << "Database initialized at:" << m_databasePath;
    emit databaseInitialized();
    
    return true;
}

QSqlDatabase DatabaseManager::database() const
{
    return QSqlDatabase::database("addon_registry");
}

QString DatabaseManager::databasePath() const
{
    return m_databasePath;
}

int DatabaseManager::schemaVersion() const
{
    return m_currentSchemaVersion;
}

bool DatabaseManager::isReady() const
{
    return m_isReady;
}

QString DatabaseManager::lastError() const
{
    return m_lastError;
}

bool DatabaseManager::initializeVersionTable()
{
    QSqlQuery query(m_database);
    
    // Create schema_version table if it doesn't exist
    QString sql = "CREATE TABLE IF NOT EXISTS schema_version ("
                  "version INTEGER PRIMARY KEY, "
                  "applied_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
                  ");";
    
    if (!query.exec(sql)) {
        m_lastError = QString("Failed to create schema_version table: %1").arg(query.lastError().text());
        qCritical() << m_lastError;
        return false;
    }
    
    // Get current schema version
    query.prepare("SELECT MAX(version) as max_version FROM schema_version;");
    if (!query.exec()) {
        m_lastError = QString("Failed to query schema version: %1").arg(query.lastError().text());
        qCritical() << m_lastError;
        return false;
    }
    
    if (query.next()) {
        if (!query.value(0).isNull()) {
            m_currentSchemaVersion = query.value(0).toInt();
        } else {
            m_currentSchemaVersion = 0;
        }
    }
    
    qDebug() << "Current schema version:" << m_currentSchemaVersion;
    return true;
}

bool DatabaseManager::applyMigrations()
{
    int latestVersion = getLatestMigrationVersion();
    
    qDebug() << "Latest migration version available:" << latestVersion;
    
    // Apply all pending migrations in sequence
    for (int version = m_currentSchemaVersion + 1; version <= latestVersion; ++version) {
        qDebug() << "Applying migration version:" << version;
        if (!applyMigration(version)) {
            return false;
        }
        
        // Record migration as applied
        QSqlQuery query(m_database);
        query.prepare("INSERT INTO schema_version (version) VALUES (?)");
        query.addBindValue(version);
        
        if (!query.exec()) {
            m_lastError = QString("Failed to record migration version %1: %2")
                    .arg(version).arg(query.lastError().text());
            qCritical() << m_lastError;
            return false;
        }
        
        m_currentSchemaVersion = version;
        emit migrationApplied(version);
    }
    
    return true;
}

bool DatabaseManager::applyMigration(int version)
{
    QString versionStr = QString::number(version).rightJustified(3, '0');
    
    // Build path to migration directory
    QString migrationDir = QCoreApplication::applicationDirPath();
    QStringList possibleDirs;
    possibleDirs << migrationDir + "/../src/database/migrations";
    possibleDirs << migrationDir + "/src/database/migrations";
    
    QString migrationPath;
    
    // Search directories dynamically for files matching versionStr_*.sql
    for (const auto& dirPath : possibleDirs) {
        QDir dir(dirPath);
        if (dir.exists()) {
            QStringList matches = dir.entryList(QStringList() << QString("%1_*.sql").arg(versionStr), QDir::Files);
            if (!matches.isEmpty()) {
                migrationPath = dir.filePath(matches.first());
                break;
            }
        }
    }
    
    // Fallback to hardcoded path patterns
    if (migrationPath.isEmpty()) {
        QStringList possiblePaths;
        possiblePaths << QString("%1/../src/database/migrations/%2_initial_schema.sql").arg(migrationDir, versionStr);
        possiblePaths << QString(":/database/migrations/%1_initial_schema.sql").arg(versionStr);
        possiblePaths << QString("%1/src/database/migrations/%2_initial_schema.sql").arg(migrationDir, versionStr);
        
        for (const auto& path : possiblePaths) {
            if (QFile::exists(path)) {
                migrationPath = path;
                break;
            }
        }
    }
    
    if (migrationPath.isEmpty()) {
        // Fallback: generate basic schema inline for version 1
        if (version == 1) {
            qDebug() << "Generating initial schema inline";
            QString sql = "CREATE TABLE IF NOT EXISTS schema_version ("
                          "version INTEGER PRIMARY KEY, "
                          "applied_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP"
                          "); "
                          "CREATE TABLE IF NOT EXISTS packs ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "uuid TEXT NOT NULL UNIQUE, "
                          "name TEXT NOT NULL, "
                          "version_major INTEGER NOT NULL, "
                          "version_minor INTEGER NOT NULL, "
                          "version_patch INTEGER NOT NULL, "
                          "pack_type TEXT NOT NULL CHECK(pack_type IN ('behavior', 'resource', 'skin')), "
                          "description TEXT, "
                          "author TEXT, "
                          "install_path TEXT NOT NULL, "
                          "is_enabled INTEGER DEFAULT 1, "
                          "installed_at TEXT DEFAULT CURRENT_TIMESTAMP, "
                          "min_engine_major INTEGER DEFAULT 1, "
                          "min_engine_minor INTEGER DEFAULT 20, "
                          "min_engine_patch INTEGER DEFAULT 0, "
                          "sort_order INTEGER DEFAULT 0"
                          "); "
                          "CREATE TABLE IF NOT EXISTS pack_dependencies ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "pack_id INTEGER NOT NULL, "
                          "dep_uuid TEXT NOT NULL, "
                          "dep_version_major INTEGER NOT NULL, "
                          "dep_version_minor INTEGER NOT NULL, "
                          "dep_version_patch INTEGER NOT NULL, "
                          "FOREIGN KEY(pack_id) REFERENCES packs(id) ON DELETE CASCADE"
                          "); "
                          "CREATE TABLE IF NOT EXISTS worlds ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "folder_name TEXT NOT NULL UNIQUE, "
                          "display_name TEXT, "
                          "world_path TEXT NOT NULL, "
                          "last_seen TEXT DEFAULT CURRENT_TIMESTAMP"
                          "); "
                          "CREATE TABLE IF NOT EXISTS world_pack_assignments ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "world_id INTEGER NOT NULL, "
                          "pack_id INTEGER NOT NULL, "
                          "sort_order INTEGER NOT NULL, "
                          "is_enabled INTEGER DEFAULT 1, "
                          "assigned_at TEXT DEFAULT CURRENT_TIMESTAMP, "
                          "FOREIGN KEY(world_id) REFERENCES worlds(id) ON DELETE CASCADE, "
                          "FOREIGN KEY(pack_id) REFERENCES packs(id) ON DELETE CASCADE, "
                          "UNIQUE(world_id, pack_id)"
                          "); "
                          "CREATE TABLE IF NOT EXISTS validation_log ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "run_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP, "
                          "trigger TEXT CHECK(trigger IN ('startup', 'manual', 'install')), "
                          "result_json TEXT, "
                          "passed INTEGER"
                          "); "
                          "CREATE INDEX IF NOT EXISTS idx_packs_uuid ON packs(uuid); "
                          "CREATE INDEX IF NOT EXISTS idx_packs_type ON packs(pack_type); "
                          "CREATE INDEX IF NOT EXISTS idx_pack_dependencies_pack_id ON pack_dependencies(pack_id); "
                          "CREATE INDEX IF NOT EXISTS idx_worlds_folder ON worlds(folder_name); "
                          "CREATE INDEX IF NOT EXISTS idx_world_pack_assignments_world_id ON world_pack_assignments(world_id); "
                          "CREATE INDEX IF NOT EXISTS idx_world_pack_assignments_pack_id ON world_pack_assignments(pack_id);";
            
            QStringList statements = sql.split(';', Qt::SkipEmptyParts);
            for (const QString& statement : statements) {
                QString trimmed = statement.trimmed();
                if (trimmed.isEmpty()) continue;
                
                QSqlQuery query(m_database);
                if (!query.exec(trimmed)) {
                    m_lastError = QString("Failed to execute inline migration: %1").arg(query.lastError().text());
                    qCritical() << m_lastError;
                    return false;
                }
            }
            return true;
        }
        
        m_lastError = QString("Migration file not found for version %1").arg(version);
        qCritical() << m_lastError;
        return false;
    }
    
    // Read migration SQL file
    QFile migrationFile(migrationPath);
    if (!migrationFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        m_lastError = QString("Failed to open migration file: %1").arg(migrationPath);
        qCritical() << m_lastError;
        return false;
    }
    
    QString sql = QString::fromUtf8(migrationFile.readAll());
    migrationFile.close();
    
    // Execute migration SQL
    QStringList statements = sql.split(';', Qt::SkipEmptyParts);
    for (const QString& statement : statements) {
        QString trimmed = statement.trimmed();
        if (trimmed.isEmpty()) continue;
        
        QSqlQuery query(m_database);
        if (!query.exec(trimmed)) {
            m_lastError = QString("Failed to execute migration %1: %2\nQuery: %3")
                    .arg(version).arg(query.lastError().text()).arg(trimmed);
            
            QFile errorLog("migration_error.txt");
            if (errorLog.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&errorLog);
                out << m_lastError;
                errorLog.close();
            }
            
            qCritical() << m_lastError;
            return false;
        }
    }
    
    qDebug() << "Successfully applied migration version" << version;
    return true;
}

int DatabaseManager::getLatestMigrationVersion() const
{
    // Look for migration files in the migrations directory
    // Pattern: NNN_*.sql where NNN is the version number
    
    QDir migrationsDir;
    
    // Try multiple possible locations
    QStringList possibleDirs;
    possibleDirs << QCoreApplication::applicationDirPath() + "/../src/database/migrations";
    possibleDirs << ":/database/migrations";
    possibleDirs << QCoreApplication::applicationDirPath() + "/src/database/migrations";
    
    for (const auto& dir : possibleDirs) {
        QDir testDir(dir);
        if (testDir.exists()) {
            migrationsDir = testDir;
            break;
        }
    }
    
    if (!migrationsDir.exists()) {
        qWarning() << "Migrations directory not found, assuming version 1";
        return 1; // Fallback: assume at least version 1 is needed
    }
    
    // Find all migration files and get the highest version
    QStringList filters;
    filters << "*.sql";
    QFileInfoList files = migrationsDir.entryInfoList(filters, QDir::Files, QDir::Name);
    
    int latestVersion = 0;
    for (const auto& fileInfo : files) {
        QString fileName = fileInfo.fileName();
        QString versionStr = fileName.split('_').first();
        
        bool ok = false;
        int version = versionStr.toInt(&ok);
        if (ok && version > latestVersion) {
            latestVersion = version;
        }
    }
    
    return (latestVersion > 0) ? latestVersion : 1;
}
