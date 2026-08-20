#ifndef DIAMONDREPOSITORY_H
#define DIAMONDREPOSITORY_H

#include "Diamond.h"
#include "DiamondImage.h"
#include <QList>
#include <optional>
#include <QVariantMap>

struct DiamondFilterCriteria {
    QString search;
    QString reference;
    QString name;
    QString status;
    QString shape;
    QString color;
    QString clarity;
    QString cut;
    QString certificateLab;
    double minCarat = 0.0;
    double maxCarat = 999.0;
    qint64 minPriceCents = 0;
    qint64 maxPriceCents = 999999999999;
    qint64 supplierId = 0;
    int hasImage = 0;
    int hasCertificate = 0;
    int isFavorite = -1;
    bool includeArchived = false;

    QString sortBy = QStringLiteral("created_at");
    bool sortAscending = false;
};

class DiamondRepository {
public:
    DiamondRepository() = default;

    QList<Diamond> getList(const DiamondFilterCriteria &criteria);
    std::optional<Diamond> getById(qint64 id);
    std::optional<Diamond> getByReference(const QString &reference);

    bool referenceExists(const QString &reference, qint64 excludeId = 0);

    bool insert(Diamond &diamond, QString *errorMessage = nullptr);
    bool update(const Diamond &diamond, QString *errorMessage = nullptr);
    bool setArchived(qint64 id, bool archived, QString *errorMessage = nullptr);
    bool setFavorite(qint64 id, bool favorite, QString *errorMessage = nullptr);
    bool setStatus(qint64 id, const QString &status, QString *errorMessage = nullptr);
    bool deletePermanently(qint64 id, QString *errorMessage = nullptr);

    bool bulkUpdateStatus(const QList<qint64> &ids, const QString &status, QString *errorMessage = nullptr);
    bool bulkAdjustSellingPricePercent(const QList<qint64> &ids, double percent, QString *errorMessage = nullptr);
    bool bulkArchive(const QList<qint64> &ids, bool archive, QString *errorMessage = nullptr);

    QList<DiamondImage> getImages(qint64 diamondId);
    bool insertImage(DiamondImage &image, QString *errorMessage = nullptr);
    bool deleteImage(qint64 imageId, QString *errorMessage = nullptr);
    bool setMainImage(qint64 diamondId, qint64 imageId, QString *errorMessage = nullptr);
};

#endif
