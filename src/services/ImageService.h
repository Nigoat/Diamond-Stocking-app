#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "DiamondImage.h"
#include <QList>
#include <QString>
#include <optional>

class ImageService {
public:
    static ImageService &instance();

    std::optional<DiamondImage> saveImageForDiamond(qint64 diamondId, const QString &sourcePath,
                                                   const QString &imageType = QStringLiteral("main"),
                                                   QString *errorMessage = nullptr);
    bool removeImage(qint64 imageId, QString *errorMessage = nullptr);
    bool setMainImage(qint64 diamondId, qint64 imageId, QString *errorMessage = nullptr);
    QList<DiamondImage> getDiamondImages(qint64 diamondId);

private:
    ImageService() = default;
    ~ImageService() = default;
    ImageService(const ImageService &) = delete;
    ImageService &operator=(const ImageService &) = delete;
};

#endif
