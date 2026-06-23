#ifndef ARCHIVEEXTRACTOR_H
#define ARCHIVEEXTRACTOR_H

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
#include <QObject>
#include <QTemporaryDir>

/**
 * @class ArchiveExtractor
 * @brief Handles extraction of Bedrock addon archive files.
 *
 * Supports .mcaddon (which can contain multiple .mcpack files), .mcpack,
 * and generic .zip archives. Extraction is done to a temporary directory.
 */
class ArchiveExtractor : public QObject
{
    Q_OBJECT

public:
    explicit ArchiveExtractor(QObject* parent = nullptr);

    enum ArchiveType {
        Unknown,
        McAddon,    ///< .mcaddon (ZIP containing .mcpack files)
        McPack,     ///< .mcpack (single addon pack)
        ZipFile     ///< Generic .zip
    };

    /**
     * @brief Detect the type of archive based on extension and content.
     * @param filePath Path to the archive file.
     * @return Detected archive type.
     */
    static ArchiveType detectArchiveType(const QString& filePath);

    /**
     * @brief Extract archive to a temporary directory.
     * @param archiveFilePath Path to the archive file to extract.
     * @return Path to the temporary extraction directory, or empty string on failure.
     */
    QString extract(const QString& archiveFilePath);

    /**
     * @brief Get the extraction directory.
     * @return Path to the temporary extraction directory.
     */
    QString extractionDirectory() const { return m_tempDir.path(); }

    /**
     * @brief Get the last error message.
     * @return Detailed error description.
     */
    QString lastError() const { return m_lastError; }

signals:
    /**
     * @brief Emitted periodically during extraction.
     * @param progressPercent Progress from 0 to 100.
     */
    void progressUpdated(int progressPercent);

    /**
     * @brief Emitted when extraction completes successfully.
     */
    void extractionCompleted();

    /**
     * @brief Emitted when an error occurs.
     * @param errorMessage Description of the error.
     */
    void error(const QString& errorMessage);

private:
    /**
     * @brief Extract a ZIP file using QZipReader (if available) or external tool.
     * @param zipFilePath Path to the ZIP file.
     * @return True if extraction succeeded; false otherwise.
     */
    bool extractZip(const QString& zipFilePath);

    /**
     * @brief Detect archive type by examining file content and extension.
     * @param filePath Path to check.
     * @return Detected type.
     */
    ArchiveType detectTypeInternal(const QString& filePath);

    QTemporaryDir m_tempDir;
    QString m_lastError;
};

#endif // ARCHIVEEXTRACTOR_H
