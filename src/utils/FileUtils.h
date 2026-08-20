#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QStringList>

class FileUtils {
public:
    static bool ensureDirExists(const QString &dirPath);
    static bool copyFile(const QString &srcPath, const QString &dstPath);
    static bool removeFile(const QString &filePath);
    static QString sanitizeFilename(const QString &filename);
    static QString formatFileSize(qint64 bytes);
    static QString fileExtension(const QString &filePath);
};

#endif
