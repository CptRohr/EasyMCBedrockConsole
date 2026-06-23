#ifndef ADDONVALIDATOR_H
#define ADDONVALIDATOR_H

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

/**
 * @class ValidationResult
 * @brief Result of a manifest validation.
 */
struct ValidationResult
{
    enum Severity {
        Valid,      ///< No issues found
        Warning,    ///< Non-critical issues
        Error       ///< Critical issues that may prevent use
    };

    Severity severity = Valid;
    QString message;
    QVector<QString> details;

    bool isValid() const { return severity == Valid; }
    bool hasWarnings() const { return severity == Warning; }
    bool hasErrors() const { return severity == Error; }
};

/**
 * @class AddonValidator
 * @brief Validates Bedrock addon manifests for correctness.
 *
 * Checks for:
 * - Valid UUID format
 * - Valid version arrays
 * - Valid manifest structure
 * - Duplicate UUID detection
 * - Pack type compatibility
 *
 * Note: Dependency resolution is handled separately by DependencyResolver.
 */
class AddonValidator
{
public:
    AddonValidator() = default;

    /**
     * @brief Validate a parsed PackManifest.
     * @param manifest The manifest to validate.
     * @return Validation result with any issues found.
     */
    static ValidationResult validate(const PackManifest& manifest);

    /**
     * @brief Check if a UUID already exists in the registry.
     * @param uuid The UUID to check.
     * @param databasePath Path to addon registry database.
     * @return True if UUID exists; false otherwise.
     */
    static bool uuidExists(const QString& uuid, const QString& databasePath = "");

    /**
     * @brief Get information about an existing pack by UUID.
     * @param uuid The UUID to look up.
     * @param databasePath Path to addon registry database.
     * @return Existing version as "major.minor.patch" or empty string if not found.
     */
    static QString getExistingPackVersion(const QString& uuid, const QString& databasePath = "");

private:
    /**
     * @brief Validate UUID format.
     * @param uuid The UUID string to validate.
     * @return True if valid UUID format; false otherwise.
     */
    static bool isValidUUID(const QString& uuid);

    /**
     * @brief Validate version array.
     * @param major Major version.
     * @param minor Minor version.
     * @param patch Patch version.
     * @return True if version is reasonable; false otherwise.
     */
    static bool isValidVersion(int major, int minor, int patch);

    /**
     * @brief Validate minimum engine version.
     * @param major Major version.
     * @param minor Minor version.
     * @param patch Patch version.
     * @return True if engine version is reasonable; false otherwise.
     */
    static bool isValidEngineVersion(int major, int minor, int patch);

    /**
     * @brief Check if pack name is reasonable.
     * @param name The pack name.
     * @return True if name is non-empty and reasonable; false otherwise.
     */
    static bool isValidPackName(const QString& name);
};

#endif // ADDONVALIDATOR_H
