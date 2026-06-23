#ifndef PACKMANIFEST_H
#define PACKMANIFEST_H

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

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QUuid>

/**
 * @class PackDependency
 * @brief Represents a dependency on another addon pack.
 */
struct PackDependency
{
    QString uuid;           ///< UUID of the dependency
    int versionMajor = 0;   ///< Major version required
    int versionMinor = 0;   ///< Minor version required
    int versionPatch = 0;   ///< Patch version required

    bool isValid() const;
    QString versionString() const;
};

/**
 * @class PackManifest
 * @brief Represents the manifest.json of a Bedrock addon pack.
 *
 * Supports both manifest format v1 and v2 as defined by Bedrock addon standards.
 * Provides parsing from JSON and validation of manifest structure.
 */
class PackManifest
{
public:
    enum PackType {
        Unknown,
        Behavior,   ///< Behavior pack (scripting, entities, blocks, etc.)
        Resource,   ///< Resource pack (textures, sounds, models, etc.)
        Skin        ///< Skin pack
    };

    PackManifest() = default;

    /**
     * @brief Parse manifest from a directory containing manifest.json.
     * @param directoryPath Path to directory with manifest.json.
     * @return PackManifest with parsed data, or invalid manifest if parsing failed.
     */
    static PackManifest parseFromDirectory(const QString& directoryPath);

    /**
     * @brief Parse manifest from JSON data.
     * @param jsonData JSON object (parsed from manifest.json).
     * @return PackManifest with parsed data.
     */
    static PackManifest parseFromJson(const QJsonObject& jsonData);

    // Properties
    bool isValid() const { return m_isValid; }
    QString errorMessage() const { return m_errorMessage; }

    QString uuid() const { return m_uuid; }
    QString name() const { return m_name; }
    QString description() const { return m_description; }
    QString author() const { return m_author; }

    int versionMajor() const { return m_versionMajor; }
    int versionMinor() const { return m_versionMinor; }
    int versionPatch() const { return m_versionPatch; }
    QString versionString() const;

    int minEngineMajor() const { return m_minEngineMajor; }
    int minEngineMinor() const { return m_minEngineMinor; }
    int minEnginePatch() const { return m_minEnginePatch; }
    QString minEngineString() const;

    PackType type() const { return m_type; }
    QString typeString() const;

    QVector<PackDependency> dependencies() const { return m_dependencies; }

    int formatVersion() const { return m_formatVersion; }

private:
    void markInvalid(const QString& error);
    void resolveLocalizations(const QString& directoryPath);

    // Parsed data
    bool m_isValid = false;
    QString m_errorMessage;
    int m_formatVersion = 0;

    QString m_uuid;
    QString m_name;
    QString m_description;
    QString m_author;

    int m_versionMajor = 0;
    int m_versionMinor = 0;
    int m_versionPatch = 0;

    int m_minEngineMajor = 1;
    int m_minEngineMinor = 20;
    int m_minEnginePatch = 0;

    PackType m_type = Unknown;

    QVector<PackDependency> m_dependencies;

    // Parsing helper methods
    bool parseVersion(const QJsonObject& versionObj, int& major, int& minor, int& patch);
    bool validateUUID(const QString& uuidStr);
    PackType determinePackType(const QJsonObject& manifestJson);
};

#endif // PACKMANIFEST_H
