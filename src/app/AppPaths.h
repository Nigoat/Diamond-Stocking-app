#ifndef APPPATHS_H
#define APPPATHS_H

#include <QString>

class AppPaths {
public:
    static AppPaths &instance();

    void initialize();

    QString appDataDir() const;
    QString databaseDir() const;
    QString databaseFilePath() const;
    QString imagesDir() const;
    QString thumbnailsDir() const;
    QString backupsDir() const;
    QString logsDir() const;
    QString exportsDir() const;

    QString diamondImagesDir(qint64 diamondId) const;
    QString diamondThumbnailsDir(qint64 diamondId) const;

private:
    AppPaths();
    ~AppPaths() = default;
    AppPaths(const AppPaths &) = delete;
    AppPaths &operator=(const AppPaths &) = delete;

    QString m_appDataDir;
};

#endif
