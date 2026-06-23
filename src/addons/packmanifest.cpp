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
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QUuid>
#include <QRegularExpression>
#include <QHash>
#include <QTextStream>

// PackDependency implementation
bool PackDependency::isValid() const
{
    return !uuid.isEmpty();
}

QString PackDependency::versionString() const
{
    return QString("%1.%2.%3").arg(versionMajor).arg(versionMinor).arg(versionPatch);
}

// PackManifest implementation
PackManifest PackManifest::parseFromDirectory(const QString& directoryPath)
{
    QFile manifestFile(QDir(directoryPath).filePath("manifest.json"));

    if (!manifestFile.exists()) {
        PackManifest manifest;
        manifest.markInvalid("manifest.json not found in directory");
        return manifest;
    }

    if (!manifestFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        PackManifest manifest;
        manifest.markInvalid("Failed to open manifest.json");
        return manifest;
    }

    QJsonDocument doc = QJsonDocument::fromJson(manifestFile.readAll());
    manifestFile.close();

    if (!doc.isObject()) {
        PackManifest manifest;
        manifest.markInvalid("Invalid JSON structure");
        return manifest;
    }

    PackManifest manifest = parseFromJson(doc.object());
    if (manifest.isValid()) {
        manifest.resolveLocalizations(directoryPath);
    }
    return manifest;
}

// Helper: parse a version field that may be either an array [1,0,0] or a string "1.0.0"
static bool parseVersionValue(const QJsonValue& val, int& major, int& minor, int& patch)
{
    if (val.isArray()) {
        QJsonArray arr = val.toArray();
        if (arr.size() < 3) return false;
        major = arr.at(0).toInt(0);
        minor = arr.at(1).toInt(0);
        patch = arr.at(2).toInt(0);
        return true;
    } else if (val.isString()) {
        QStringList parts = val.toString().split('.');
        if (parts.size() < 3) return false;
        bool ok1, ok2, ok3;
        major = parts[0].toInt(&ok1);
        minor = parts[1].toInt(&ok2);
        patch = parts[2].toInt(&ok3);
        return ok1 && ok2 && ok3;
    }
    return false;
}

PackManifest PackManifest::parseFromJson(const QJsonObject& jsonData)
{
    PackManifest manifest;

    // Check format version — handle both integer and string representations
    // e.g. some addons write "format_version": "3" (string) rather than 3 (int)
    {
        QJsonValue fv = jsonData.value("format_version");
        if (fv.isDouble()) {
            manifest.m_formatVersion = fv.toInt(1);
        } else if (fv.isString()) {
            bool ok = false;
            int parsed = fv.toString().toInt(&ok);
            manifest.m_formatVersion = ok ? parsed : 1;
        } else {
            manifest.m_formatVersion = 1; // default to v1 if missing
        }
    }

    if (manifest.m_formatVersion == 1) {
        // Format v1 structure
        manifest.m_uuid = jsonData.value("uuid").toString();
        manifest.m_name = jsonData.value("name").toString();
        manifest.m_description = jsonData.value("description").toString();
        manifest.m_author = jsonData.value("author").toString();

        // Parse version (array [1,0,0] or string "1.0.0")
        if (!parseVersionValue(jsonData.value("version"),
                               manifest.m_versionMajor, manifest.m_versionMinor, manifest.m_versionPatch)) {
            manifest.markInvalid("Invalid version format");
            return manifest;
        }

        // Parse min_engine_version (array or string, non-fatal if missing/malformed)
        parseVersionValue(jsonData.value("min_engine_version"),
                          manifest.m_minEngineMajor, manifest.m_minEngineMinor, manifest.m_minEnginePatch);

        // Determine pack type (not explicitly in v1, infer from modules)
        manifest.m_type = manifest.determinePackType(jsonData);

        // Parse dependencies
        QJsonArray depsArray = jsonData.value("dependencies").toArray();
        for (const auto& depVal : depsArray) {
            QJsonObject depObj = depVal.toObject();
            PackDependency dep;
            dep.uuid = depObj.value("uuid").toString();

            parseVersionValue(depObj.value("version"),
                              dep.versionMajor, dep.versionMinor, dep.versionPatch);

            if (dep.isValid()) {
                manifest.m_dependencies.append(dep);
            }
        }

    } else if (manifest.m_formatVersion == 2) {
        // Format v2 structure with header and modules
        QJsonObject headerObj = jsonData.value("header").toObject();

        manifest.m_uuid = headerObj.value("uuid").toString();
        manifest.m_name = headerObj.value("name").toString();
        manifest.m_description = headerObj.value("description").toString();

        // Parse version (array [1,0,0] or string "1.0.0")
        if (!parseVersionValue(headerObj.value("version"),
                               manifest.m_versionMajor, manifest.m_versionMinor, manifest.m_versionPatch)) {
            manifest.markInvalid("Invalid version format in header");
            return manifest;
        }

        // Parse min_engine_version (non-fatal if missing/malformed)
        parseVersionValue(headerObj.value("min_engine_version"),
                          manifest.m_minEngineMajor, manifest.m_minEngineMinor, manifest.m_minEnginePatch);

        // Determine pack type from modules
        manifest.m_type = manifest.determinePackType(jsonData);

        // Parse dependencies (same as v1)
        QJsonArray depsArray = jsonData.value("dependencies").toArray();
        for (const auto& depVal : depsArray) {
            QJsonObject depObj = depVal.toObject();
            PackDependency dep;
            dep.uuid = depObj.value("uuid").toString();

            parseVersionValue(depObj.value("version"),
                              dep.versionMajor, dep.versionMinor, dep.versionPatch);

            if (dep.isValid()) {
                manifest.m_dependencies.append(dep);
            }
        }
    } else if (manifest.m_formatVersion >= 3) {
        // Format v3+ uses the same structure as v2 (header + modules)
        QJsonObject headerObj = jsonData.value("header").toObject();

        manifest.m_uuid = headerObj.value("uuid").toString();
        manifest.m_name = headerObj.value("name").toString();
        manifest.m_description = headerObj.value("description").toString();

        // Parse version (array [1,0,0] or string "1.0.0")
        if (!parseVersionValue(headerObj.value("version"),
                               manifest.m_versionMajor, manifest.m_versionMinor, manifest.m_versionPatch)) {
            manifest.markInvalid("Invalid version format in header");
            return manifest;
        }

        // Parse min_engine_version (non-fatal if missing/malformed)
        parseVersionValue(headerObj.value("min_engine_version"),
                          manifest.m_minEngineMajor, manifest.m_minEngineMinor, manifest.m_minEnginePatch);

        // Determine pack type from modules
        manifest.m_type = manifest.determinePackType(jsonData);

        // Parse dependencies (same as v1/v2)
        QJsonArray depsArray = jsonData.value("dependencies").toArray();
        for (const auto& depVal : depsArray) {
            QJsonObject depObj = depVal.toObject();
            PackDependency dep;
            dep.uuid = depObj.value("uuid").toString();

            parseVersionValue(depObj.value("version"),
                              dep.versionMajor, dep.versionMinor, dep.versionPatch);

            if (dep.isValid()) {
                manifest.m_dependencies.append(dep);
            }
        }
    } else {
        manifest.markInvalid(QString("Unsupported manifest format version: %1").arg(manifest.m_formatVersion));
        return manifest;
    }

    // Validate essential fields
    if (manifest.m_uuid.isEmpty()) {
        manifest.markInvalid("UUID is required and cannot be empty");
        return manifest;
    }

    if (!manifest.validateUUID(manifest.m_uuid)) {
        manifest.markInvalid(QString("Invalid UUID format: %1").arg(manifest.m_uuid));
        return manifest;
    }

    if (manifest.m_name.isEmpty()) {
        manifest.markInvalid("Pack name is required");
        return manifest;
    }

    if (manifest.m_type == Unknown) {
        manifest.markInvalid("Cannot determine pack type from manifest");
        return manifest;
    }

    manifest.m_isValid = true;
    return manifest;
}

QString PackManifest::versionString() const
{
    return QString("%1.%2.%3").arg(m_versionMajor).arg(m_versionMinor).arg(m_versionPatch);
}

QString PackManifest::minEngineString() const
{
    return QString("%1.%2.%3").arg(m_minEngineMajor).arg(m_minEngineMinor).arg(m_minEnginePatch);
}

QString PackManifest::typeString() const
{
    switch (m_type) {
    case Behavior: return "behavior";
    case Resource: return "resource";
    case Skin: return "skin";
    case Unknown:
    default: return "unknown";
    }
}

void PackManifest::markInvalid(const QString& error)
{
    m_isValid = false;
    m_errorMessage = error;
    qWarning() << "PackManifest error:" << error;
}

bool PackManifest::validateUUID(const QString& uuidStr)
{
    // Check if it's a valid UUID format (8-4-4-4-12)
    QRegularExpression uuidRegex("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$");
    return uuidRegex.match(uuidStr).hasMatch();
}

PackManifest::PackType PackManifest::determinePackType(const QJsonObject& manifestJson)
{
    // Try format v2 first (check modules)
    QJsonArray modulesArray = manifestJson.value("modules").toArray();
    if (!modulesArray.isEmpty()) {
        for (const auto& moduleVal : modulesArray) {
            QJsonObject moduleObj = moduleVal.toObject();
            QString typeStr = moduleObj.value("type").toString();

            if (typeStr == "data" || typeStr == "script") {
                return Behavior;
            } else if (typeStr == "resources") {
                return Resource;
            } else if (typeStr == "skin") {
                return Skin;
            }
        }
    }

    // Fallback for format v1: check if directories exist (inferred from common structure)
    // This is a heuristic - we rely on the pack structure
    // In a real scenario, we'd also check on-disk structure

    return Resource; // Default fallback
}

void PackManifest::resolveLocalizations(const QString& directoryPath)
{
    QDir textsDir(QDir(directoryPath).filePath("texts"));
    if (!textsDir.exists()) {
        return;
    }

    // List of files to check in order of preference
    QStringList filesToCheck;
    filesToCheck << "en_US.lang" << "en_GB.lang";

    // Scan for any other .lang files in the texts directory
    QStringList allLangFiles = textsDir.entryList(QStringList() << "*.lang", QDir::Files);
    for (const QString& file : allLangFiles) {
        if (file != "en_US.lang" && file != "en_GB.lang") {
            filesToCheck << file;
        }
    }

    QString langFilePath;
    for (const QString& file : filesToCheck) {
        QString fullPath = textsDir.filePath(file);
        if (QFile::exists(fullPath)) {
            langFilePath = fullPath;
            break;
        }
    }

    if (langFilePath.isEmpty()) {
        return;
    }

    QFile file(langFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QHash<QString, QString> translations;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith('#')) {
            continue;
        }
        int eqIdx = line.indexOf('=');
        if (eqIdx <= 0) {
            continue;
        }
        QString key = line.left(eqIdx).trimmed();
        QString val = line.mid(eqIdx + 1);
        int commentIdx = val.indexOf("##");
        if (commentIdx != -1) {
            val = val.left(commentIdx);
        }
        val = val.trimmed();
        translations[key] = val;
    }

    // Resolve name and description if they exist in translations
    if (translations.contains(m_name)) {
        m_name = translations[m_name];
    }
    if (translations.contains(m_description)) {
        m_description = translations[m_description];
    }
}
