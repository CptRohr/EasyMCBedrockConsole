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

#include "addonvalidator.h"
#include "database/databasemanager.h"
#include <QDebug>
#include <QRegularExpression>
#include <QSqlQuery>
#include <QSqlError>

ValidationResult AddonValidator::validate(const PackManifest& manifest)
{
    ValidationResult result;

    // Check if manifest was parsed successfully
    if (!manifest.isValid()) {
        result.severity = ValidationResult::Error;
        result.message = "Manifest parsing failed";
        result.details.append(manifest.errorMessage());
        return result;
    }

    // Validate UUID format
    if (!isValidUUID(manifest.uuid())) {
        result.severity = ValidationResult::Error;
        result.message = "Invalid UUID format";
        result.details.append(QString("UUID: %1").arg(manifest.uuid()));
        return result;
    }

    // Validate version
    if (!isValidVersion(manifest.versionMajor(), manifest.versionMinor(), manifest.versionPatch())) {
        result.severity = ValidationResult::Error;
        result.message = "Invalid version format";
        result.details.append(QString("Version: %1").arg(manifest.versionString()));
        return result;
    }

    // Validate minimum engine version
    if (!isValidEngineVersion(manifest.minEngineMajor(), manifest.minEngineMinor(), manifest.minEnginePatch())) {
        result.severity = ValidationResult::Warning;
        result.message = "Unusual minimum engine version";
        result.details.append(QString("Min Engine: %1").arg(manifest.minEngineString()));
    }

    // Validate pack name
    if (!isValidPackName(manifest.name())) {
        result.severity = ValidationResult::Error;
        result.message = "Invalid pack name";
        result.details.append("Pack name is empty or contains invalid characters");
        return result;
    }

    // Validate pack type
    if (manifest.type() == PackManifest::Unknown) {
        result.severity = ValidationResult::Error;
        result.message = "Unable to determine pack type";
        result.details.append("Pack must be behavior, resource, or skin type");
        return result;
    }

    // Validate dependencies have valid UUIDs
    for (const auto& dep : manifest.dependencies()) {
        if (!isValidUUID(dep.uuid)) {
            result.severity = ValidationResult::Error;
            result.message = "Invalid UUID in dependency";
            result.details.append(QString("Dependency UUID: %1").arg(dep.uuid));
            return result;
        }

        if (!isValidVersion(dep.versionMajor, dep.versionMinor, dep.versionPatch)) {
            result.severity = ValidationResult::Warning;
            result.message = "Invalid version in dependency";
            result.details.append(QString("Dependency: %1 version %2")
                                 .arg(dep.uuid, dep.versionString()));
        }
    }

    // All validations passed
    if (result.severity == ValidationResult::Valid) {
        result.message = "Manifest is valid";
    }

    return result;
}

bool AddonValidator::uuidExists(const QString& uuid, const QString& databasePath)
{
    try {
        DatabaseManager& dbMgr = DatabaseManager::instance(databasePath);
        if (!dbMgr.isReady()) {
            qWarning() << "Database not ready for UUID check";
            return false;
        }

        QSqlQuery query(dbMgr.database());
        query.prepare("SELECT COUNT(*) FROM packs WHERE uuid = ?");
        query.addBindValue(uuid);

        if (!query.exec()) {
            qWarning() << "Failed to query pack UUID:" << query.lastError().text();
            return false;
        }

        if (query.next()) {
            return query.value(0).toInt() > 0;
        }
    } catch (...) {
        qWarning() << "Exception checking UUID existence";
    }

    return false;
}

QString AddonValidator::getExistingPackVersion(const QString& uuid, const QString& databasePath)
{
    try {
        DatabaseManager& dbMgr = DatabaseManager::instance(databasePath);
        if (!dbMgr.isReady()) {
            return "";
        }

        QSqlQuery query(dbMgr.database());
        query.prepare("SELECT version_major, version_minor, version_patch FROM packs WHERE uuid = ?");
        query.addBindValue(uuid);

        if (!query.exec()) {
            qWarning() << "Failed to query pack version:" << query.lastError().text();
            return "";
        }

        if (query.next()) {
            int major = query.value(0).toInt();
            int minor = query.value(1).toInt();
            int patch = query.value(2).toInt();
            return QString("%1.%2.%3").arg(major).arg(minor).arg(patch);
        }
    } catch (...) {
        qWarning() << "Exception getting pack version";
    }

    return "";
}

bool AddonValidator::isValidUUID(const QString& uuid)
{
    // UUID format: 8-4-4-4-12 hexadecimal digits
    QRegularExpression uuidPattern("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$");
    return uuidPattern.match(uuid).hasMatch();
}

bool AddonValidator::isValidVersion(int major, int minor, int patch)
{
    // Versions should be non-negative and reasonable
    // Very large numbers (>9999) are suspicious but possible
    return major >= 0 && minor >= 0 && patch >= 0 &&
           major < 10000 && minor < 10000 && patch < 10000;
}

bool AddonValidator::isValidEngineVersion(int major, int minor, int patch)
{
    // Engine version should be between 1.0.0 and a reasonable maximum
    // Older logic capped minor < 100 and patch < 100; increase limits to cover future Bedrock versions
    return major > 0 && major < 100 &&
           minor >= 0 && minor < 1000 &&
           patch >= 0 && patch < 1000;
}

bool AddonValidator::isValidPackName(const QString& name)
{
    // Pack name should not be empty and should be reasonable length
    return !name.isEmpty() && name.length() < 256 && name.trimmed() == name;
}
