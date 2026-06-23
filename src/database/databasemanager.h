#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

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
#include <QSqlDatabase>
#include <QString>

/**
 * @class DatabaseManager
 * @brief Singleton manager for SQLite database connection and schema migrations.
 *
 * Handles database initialization, connection pooling, and automatic schema version
 * management. All addon and world data is persisted via this manager.
 */
class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Get the singleton instance of DatabaseManager.
     * @param serverRootPath Path to the server root directory where addon_registry.db is stored.
     * @return Reference to the singleton instance.
     */
    static DatabaseManager& instance(const QString& serverRootPath = "");

    /**
     * @brief Initialize the database connection.
     * @param serverRootPath Path to the server root directory.
     * @return True if initialization and migrations succeeded; false otherwise.
     */
    bool initialize(const QString& serverRootPath);

    /**
     * @brief Get the active database connection.
     * @return QSqlDatabase object ready for queries.
     */
    QSqlDatabase database() const;

    /**
     * @brief Get the path to the database file.
     * @return Absolute path to addon_registry.db.
     */
    QString databasePath() const;

    /**
     * @brief Get the current schema version.
     * @return Version number of the applied schema.
     */
    int schemaVersion() const;

    /**
     * @brief Check if database is ready for use.
     * @return True if connection is open and schema is current.
     */
    bool isReady() const;

    /**
     * @brief Get the last error message.
     * @return Detailed error description.
     */
    QString lastError() const;

signals:
    /**
     * @brief Emitted when database is successfully initialized.
     */
    void databaseInitialized();

    /**
     * @brief Emitted when a schema migration completes.
     * @param version The version that was applied.
     */
    void migrationApplied(int version);

    /**
     * @brief Emitted when a critical error occurs.
     * @param errorMessage Description of the error.
     */
    void error(const QString& errorMessage);

private:
    explicit DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager() = default;

    // Singleton prevention
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    /**
     * @brief Apply pending schema migrations.
     * @return True if all migrations succeeded; false otherwise.
     */
    bool applyMigrations();

    /**
     * @brief Load a migration SQL file and execute it.
     * @param version The migration version number.
     * @return True if migration succeeded; false otherwise.
     */
    bool applyMigration(int version);

    /**
     * @brief Get the latest available migration version.
     * @return The highest version number found in migrations folder.
     */
    int getLatestMigrationVersion() const;

    /**
     * @brief Initialize the schema_version tracking table.
     * @return True if successful; false otherwise.
     */
    bool initializeVersionTable();

    QSqlDatabase m_database;
    QString m_databasePath;
    QString m_serverRootPath;
    QString m_lastError;
    int m_currentSchemaVersion;
    bool m_isReady;

    static DatabaseManager* m_instance;
};

#endif // DATABASEMANAGER_H
