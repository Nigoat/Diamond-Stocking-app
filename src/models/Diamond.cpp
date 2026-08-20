#include "Diamond.h"
#include <QLocale>

Diamond::Diamond()
    : m_id(0)
    , m_shape(QStringLiteral("Round"))
    , m_caratWeight(0.0)
    , m_color(QStringLiteral("G"))
    , m_clarity(QStringLiteral("VS1"))
    , m_cut(QStringLiteral("Excellent"))
    , m_polish(QStringLiteral("Excellent"))
    , m_symmetry(QStringLiteral("Very Good"))
    , m_fluorescence(QStringLiteral("None"))
    , m_tablePercentage(0.0)
    , m_depthPercentage(0.0)
    , m_lengthMm(0.0)
    , m_widthMm(0.0)
    , m_heightMm(0.0)
    , m_certificateLab(QStringLiteral("None"))
    , m_purchasePriceCents(0)
    , m_sellingPriceCents(0)
    , m_discountPriceCents(0)
    , m_minSellingPriceCents(0)
    , m_status(QStringLiteral("Available"))
    , m_location(QStringLiteral("Store"))
    , m_supplierId(0)
    , m_isFavorite(false)
    , m_archived(false)
    , m_imageCount(0)
{
}

QString Diamond::measurementsFormatted() const {
    if (m_lengthMm <= 0.0 && m_widthMm <= 0.0 && m_heightMm <= 0.0) {
        return QStringLiteral("-");
    }
    return QStringLiteral("%1 x %2 x %3 mm")
        .arg(QString::number(m_lengthMm, 'f', 2),
             QString::number(m_widthMm, 'f', 2),
             QString::number(m_heightMm, 'f', 2));
}

QVariantMap Diamond::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("id")] = m_id;
    map[QStringLiteral("reference")] = m_reference;
    map[QStringLiteral("sku")] = m_sku;
    map[QStringLiteral("barcode")] = m_barcode;
    map[QStringLiteral("name")] = m_name;
    map[QStringLiteral("description")] = m_description;
    map[QStringLiteral("shape")] = m_shape;
    map[QStringLiteral("caratWeight")] = m_caratWeight;
    map[QStringLiteral("color")] = m_color;
    map[QStringLiteral("clarity")] = m_clarity;
    map[QStringLiteral("cut")] = m_cut;
    map[QStringLiteral("polish")] = m_polish;
    map[QStringLiteral("symmetry")] = m_symmetry;
    map[QStringLiteral("fluorescence")] = m_fluorescence;
    map[QStringLiteral("fluorescenceColor")] = m_fluorescenceColor;
    map[QStringLiteral("tablePercentage")] = m_tablePercentage;
    map[QStringLiteral("depthPercentage")] = m_depthPercentage;
    map[QStringLiteral("lengthMm")] = m_lengthMm;
    map[QStringLiteral("widthMm")] = m_widthMm;
    map[QStringLiteral("heightMm")] = m_heightMm;
    map[QStringLiteral("girdle")] = m_girdle;
    map[QStringLiteral("culet")] = m_culet;
    map[QStringLiteral("certificateNumber")] = m_certificateNumber;
    map[QStringLiteral("certificateLab")] = m_certificateLab;
    map[QStringLiteral("certificateDate")] = m_certificateDate;
    map[QStringLiteral("certificateUrl")] = m_certificateUrl;
    map[QStringLiteral("certificateNotes")] = m_certificateNotes;
    map[QStringLiteral("purchasePriceCents")] = m_purchasePriceCents;
    map[QStringLiteral("sellingPriceCents")] = m_sellingPriceCents;
    map[QStringLiteral("discountPriceCents")] = m_discountPriceCents;
    map[QStringLiteral("minSellingPriceCents")] = m_minSellingPriceCents;
    map[QStringLiteral("purchasePriceFormatted")] = purchasePrice().formatted();
    map[QStringLiteral("sellingPriceFormatted")] = sellingPrice().formatted();
    map[QStringLiteral("discountPriceFormatted")] = discountPrice().formatted();
    map[QStringLiteral("minSellingPriceFormatted")] = minSellingPrice().formatted();
    map[QStringLiteral("marginFormatted")] = margin().formatted();
    map[QStringLiteral("marginPercentage")] = marginPercentage();
    map[QStringLiteral("status")] = m_status;
    map[QStringLiteral("location")] = m_location;
    map[QStringLiteral("locationDetails")] = m_locationDetails;
    map[QStringLiteral("supplierId")] = m_supplierId;
    map[QStringLiteral("supplierName")] = m_supplierName;
    map[QStringLiteral("isFavorite")] = m_isFavorite;
    map[QStringLiteral("archived")] = m_archived;
    map[QStringLiteral("createdAt")] = m_createdAt;
    map[QStringLiteral("updatedAt")] = m_updatedAt;
    map[QStringLiteral("mainImageThumbnail")] = m_mainImageThumbnail;
    map[QStringLiteral("mainImageFile")] = m_mainImageFile;
    map[QStringLiteral("imageCount")] = m_imageCount;
    map[QStringLiteral("measurementsFormatted")] = measurementsFormatted();
    return map;
}

Diamond Diamond::fromVariantMap(const QVariantMap &map) {
    Diamond d;
    d.setId(map.value(QStringLiteral("id"), 0).toLongLong());
    d.setReference(map.value(QStringLiteral("reference")).toString());
    d.setSku(map.value(QStringLiteral("sku")).toString());
    d.setBarcode(map.value(QStringLiteral("barcode")).toString());
    d.setName(map.value(QStringLiteral("name")).toString());
    d.setDescription(map.value(QStringLiteral("description")).toString());
    d.setShape(map.value(QStringLiteral("shape"), QStringLiteral("Round")).toString());
    d.setCartWeight(map.value(QStringLiteral("caratWeight"), 0.0).toDouble());
    d.setColor(map.value(QStringLiteral("color"), QStringLiteral("G")).toString());
    d.setClarity(map.value(QStringLiteral("clarity"), QStringLiteral("VS1")).toString());
    d.setCut(map.value(QStringLiteral("cut"), QStringLiteral("Excellent")).toString());
    d.setPolish(map.value(QStringLiteral("polish"), QStringLiteral("Excellent")).toString());
    d.setSymmetry(map.value(QStringLiteral("symmetry"), QStringLiteral("Very Good")).toString());
    d.setFluorescence(map.value(QStringLiteral("fluorescence"), QStringLiteral("None")).toString());
    d.setFluorescenceColor(map.value(QStringLiteral("fluorescenceColor")).toString());
    d.setTablePercentage(map.value(QStringLiteral("tablePercentage"), 0.0).toDouble());
    d.setDepthPercentage(map.value(QStringLiteral("depthPercentage"), 0.0).toDouble());
    d.setLengthMm(map.value(QStringLiteral("lengthMm"), 0.0).toDouble());
    d.setWidthMm(map.value(QStringLiteral("widthMm"), 0.0).toDouble());
    d.setHeightMm(map.value(QStringLiteral("heightMm"), 0.0).toDouble());
    d.setGirdle(map.value(QStringLiteral("girdle")).toString());
    d.setCulet(map.value(QStringLiteral("culet")).toString());
    d.setCertificateNumber(map.value(QStringLiteral("certificateNumber")).toString());
    d.setCertificateLab(map.value(QStringLiteral("certificateLab"), QStringLiteral("None")).toString());
    d.setCertificateDate(map.value(QStringLiteral("certificateDate")).toString());
    d.setCertificateUrl(map.value(QStringLiteral("certificateUrl")).toString());
    d.setCertificateNotes(map.value(QStringLiteral("certificateNotes")).toString());

    if (map.contains(QStringLiteral("purchasePriceCents"))) {
        d.setPurchasePriceCents(map.value(QStringLiteral("purchasePriceCents")).toLongLong());
    } else if (map.contains(QStringLiteral("purchasePrice"))) {
        d.setPurchasePriceCents(Money::fromDouble(map.value(QStringLiteral("purchasePrice")).toDouble()).cents());
    }

    if (map.contains(QStringLiteral("sellingPriceCents"))) {
        d.setSellingPriceCents(map.value(QStringLiteral("sellingPriceCents")).toLongLong());
    } else if (map.contains(QStringLiteral("sellingPrice"))) {
        d.setSellingPriceCents(Money::fromDouble(map.value(QStringLiteral("sellingPrice")).toDouble()).cents());
    }

    if (map.contains(QStringLiteral("discountPriceCents"))) {
        d.setDiscountPriceCents(map.value(QStringLiteral("discountPriceCents")).toLongLong());
    } else if (map.contains(QStringLiteral("discountPrice"))) {
        d.setDiscountPriceCents(Money::fromDouble(map.value(QStringLiteral("discountPrice")).toDouble()).cents());
    }

    if (map.contains(QStringLiteral("minSellingPriceCents"))) {
        d.setMinSellingPriceCents(map.value(QStringLiteral("minSellingPriceCents")).toLongLong());
    } else if (map.contains(QStringLiteral("minSellingPrice"))) {
        d.setMinSellingPriceCents(Money::fromDouble(map.value(QStringLiteral("minSellingPrice")).toDouble()).cents());
    }

    d.setStatus(map.value(QStringLiteral("status"), QStringLiteral("Available")).toString());
    d.setLocation(map.value(QStringLiteral("location"), QStringLiteral("Store")).toString());
    d.setLocationDetails(map.value(QStringLiteral("locationDetails")).toString());
    d.setSupplierId(map.value(QStringLiteral("supplierId"), 0).toLongLong());
    d.setSupplierName(map.value(QStringLiteral("supplierName")).toString());
    d.setIsFavorite(map.value(QStringLiteral("isFavorite"), false).toBool());
    d.setArchived(map.value(QStringLiteral("archived"), false).toBool());
    d.setCreatedAt(map.value(QStringLiteral("createdAt")).toString());
    d.setUpdatedAt(map.value(QStringLiteral("updatedAt")).toString());
    d.setMainImageThumbnail(map.value(QStringLiteral("mainImageThumbnail")).toString());
    d.setMainImageFile(map.value(QStringLiteral("mainImageFile")).toString());
    d.setImageCount(map.value(QStringLiteral("imageCount"), 0).toInt());
    return d;
}
