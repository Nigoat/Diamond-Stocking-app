#include "DiamondImage.h"

DiamondImage::DiamondImage()
    : m_id(0)
    , m_diamondId(0)
    , m_imageType(QStringLiteral("main"))
    , m_sortOrder(0)
{
}

QVariantMap DiamondImage::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("id")] = m_id;
    map[QStringLiteral("diamondId")] = m_diamondId;
    map[QStringLiteral("filePath")] = m_filePath;
    map[QStringLiteral("thumbnailPath")] = m_thumbnailPath;
    map[QStringLiteral("imageType")] = m_imageType;
    map[QStringLiteral("sortOrder")] = m_sortOrder;
    map[QStringLiteral("createdAt")] = m_createdAt;
    return map;
}

DiamondImage DiamondImage::fromVariantMap(const QVariantMap &map) {
    DiamondImage img;
    img.setId(map.value(QStringLiteral("id"), 0).toLongLong());
    img.setDiamondId(map.value(QStringLiteral("diamondId"), 0).toLongLong());
    img.setFilePath(map.value(QStringLiteral("filePath")).toString());
    img.setThumbnailPath(map.value(QStringLiteral("thumbnailPath")).toString());
    img.setImageType(map.value(QStringLiteral("imageType"), QStringLiteral("main")).toString());
    img.setSortOrder(map.value(QStringLiteral("sortOrder"), 0).toInt());
    img.setCreatedAt(map.value(QStringLiteral("createdAt")).toString());
    return img;
}
