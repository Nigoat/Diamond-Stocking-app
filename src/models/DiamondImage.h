#ifndef DIAMONDIMAGE_H
#define DIAMONDIMAGE_H

#include <QString>
#include <QVariantMap>

class DiamondImage {
public:
    DiamondImage();

    qint64 id() const { return m_id; }
    void setId(qint64 id) { m_id = id; }

    qint64 diamondId() const { return m_diamondId; }
    void setDiamondId(qint64 id) { m_diamondId = id; }

    QString filePath() const { return m_filePath; }
    void setFilePath(const QString &path) { m_filePath = path; }

    QString thumbnailPath() const { return m_thumbnailPath; }
    void setThumbnailPath(const QString &path) { m_thumbnailPath = path; }

    QString imageType() const { return m_imageType; }
    void setImageType(const QString &type) { m_imageType = type; }

    int sortOrder() const { return m_sortOrder; }
    void setSortOrder(int order) { m_sortOrder = order; }

    QString createdAt() const { return m_createdAt; }
    void setCreatedAt(const QString &createdAt) { m_createdAt = createdAt; }

    QVariantMap toVariantMap() const;
    static DiamondImage fromVariantMap(const QVariantMap &map);

private:
    qint64 m_id;
    qint64 m_diamondId;
    QString m_filePath;
    QString m_thumbnailPath;
    QString m_imageType;
    int m_sortOrder;
    QString m_createdAt;
};

#endif
