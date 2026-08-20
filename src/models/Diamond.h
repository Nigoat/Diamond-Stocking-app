#ifndef DIAMOND_H
#define DIAMOND_H

#include <QString>
#include <QVariantMap>
#include "Money.h"

class Diamond {
public:
    Diamond();

    qint64 id() const { return m_id; }
    void setId(qint64 id) { m_id = id; }

    QString reference() const { return m_reference; }
    void setReference(const QString &ref) { m_reference = ref; }

    QString sku() const { return m_sku; }
    void setSku(const QString &sku) { m_sku = sku; }

    QString barcode() const { return m_barcode; }
    void setBarcode(const QString &code) { m_barcode = code; }

    QString name() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QString description() const { return m_description; }
    void setDescription(const QString &desc) { m_description = desc; }

    QString shape() const { return m_shape; }
    void setShape(const QString &shape) { m_shape = shape; }

    double caratWeight() const { return m_caratWeight; }
    void setCartWeight(double weight) { m_caratWeight = weight; }

    QString color() const { return m_color; }
    void setColor(const QString &color) { m_color = color; }

    QString clarity() const { return m_clarity; }
    void setClarity(const QString &clarity) { m_clarity = clarity; }

    QString cut() const { return m_cut; }
    void setCut(const QString &cut) { m_cut = cut; }

    QString polish() const { return m_polish; }
    void setPolish(const QString &polish) { m_polish = polish; }

    QString symmetry() const { return m_symmetry; }
    void setSymmetry(const QString &symmetry) { m_symmetry = symmetry; }

    QString fluorescence() const { return m_fluorescence; }
    void setFluorescence(const QString &fluo) { m_fluorescence = fluo; }

    QString fluorescenceColor() const { return m_fluorescenceColor; }
    void setFluorescenceColor(const QString &color) { m_fluorescenceColor = color; }

    double tablePercentage() const { return m_tablePercentage; }
    void setTablePercentage(double table) { m_tablePercentage = table; }

    double depthPercentage() const { return m_depthPercentage; }
    void setDepthPercentage(double depth) { m_depthPercentage = depth; }

    double lengthMm() const { return m_lengthMm; }
    void setLengthMm(double length) { m_lengthMm = length; }

    double widthMm() const { return m_widthMm; }
    void setWidthMm(double width) { m_widthMm = width; }

    double heightMm() const { return m_heightMm; }
    void setHeightMm(double height) { m_heightMm = height; }

    QString girdle() const { return m_girdle; }
    void setGirdle(const QString &girdle) { m_girdle = girdle; }

    QString culet() const { return m_culet; }
    void setCulet(const QString &culet) { m_culet = culet; }

    QString certificateNumber() const { return m_certificateNumber; }
    void setCertificateNumber(const QString &num) { m_certificateNumber = num; }

    QString certificateLab() const { return m_certificateLab; }
    void setCertificateLab(const QString &lab) { m_certificateLab = lab; }

    QString certificateDate() const { return m_certificateDate; }
    void setCertificateDate(const QString &date) { m_certificateDate = date; }

    QString certificateUrl() const { return m_certificateUrl; }
    void setCertificateUrl(const QString &url) { m_certificateUrl = url; }

    QString certificateNotes() const { return m_certificateNotes; }
    void setCertificateNotes(const QString &notes) { m_certificateNotes = notes; }

    qint64 purchasePriceCents() const { return m_purchasePriceCents; }
    void setPurchasePriceCents(qint64 cents) { m_purchasePriceCents = cents; }

    qint64 sellingPriceCents() const { return m_sellingPriceCents; }
    void setSellingPriceCents(qint64 cents) { m_sellingPriceCents = cents; }

    qint64 discountPriceCents() const { return m_discountPriceCents; }
    void setDiscountPriceCents(qint64 cents) { m_discountPriceCents = cents; }

    qint64 minSellingPriceCents() const { return m_minSellingPriceCents; }
    void setMinSellingPriceCents(qint64 cents) { m_minSellingPriceCents = cents; }

    QString status() const { return m_status; }
    void setStatus(const QString &status) { m_status = status; }

    QString location() const { return m_location; }
    void setLocation(const QString &loc) { m_location = loc; }

    QString locationDetails() const { return m_locationDetails; }
    void setLocationDetails(const QString &det) { m_locationDetails = det; }

    qint64 supplierId() const { return m_supplierId; }
    void setSupplierId(qint64 id) { m_supplierId = id; }

    QString supplierName() const { return m_supplierName; }
    void setSupplierName(const QString &name) { m_supplierName = name; }

    bool isFavorite() const { return m_isFavorite; }
    void setIsFavorite(bool fav) { m_isFavorite = fav; }

    bool archived() const { return m_archived; }
    void setArchived(bool arch) { m_archived = arch; }

    QString createdAt() const { return m_createdAt; }
    void setCreatedAt(const QString &created) { m_createdAt = created; }

    QString updatedAt() const { return m_updatedAt; }
    void setUpdatedAt(const QString &updated) { m_updatedAt = updated; }

    QString mainImageThumbnail() const { return m_mainImageThumbnail; }
    void setMainImageThumbnail(const QString &path) { m_mainImageThumbnail = path; }

    QString mainImageFile() const { return m_mainImageFile; }
    void setMainImageFile(const QString &path) { m_mainImageFile = path; }

    int imageCount() const { return m_imageCount; }
    void setImageCount(int count) { m_imageCount = count; }

    Money purchasePrice() const { return Money::fromCents(m_purchasePriceCents); }
    Money sellingPrice() const { return Money::fromCents(m_sellingPriceCents); }
    Money discountPrice() const { return Money::fromCents(m_discountPriceCents); }
    Money minSellingPrice() const { return Money::fromCents(m_minSellingPriceCents); }

    Money margin() const { return Money::calculateMargin(sellingPrice(), purchasePrice()); }
    double marginPercentage() const { return Money::calculateMarginPercentage(sellingPrice(), purchasePrice()); }

    QString measurementsFormatted() const;

    QVariantMap toVariantMap() const;
    static Diamond fromVariantMap(const QVariantMap &map);

private:
    qint64 m_id;
    QString m_reference;
    QString m_sku;
    QString m_barcode;
    QString m_name;
    QString m_description;
    QString m_shape;
    double m_caratWeight;
    QString m_color;
    QString m_clarity;
    QString m_cut;
    QString m_polish;
    QString m_symmetry;
    QString m_fluorescence;
    QString m_fluorescenceColor;
    double m_tablePercentage;
    double m_depthPercentage;
    double m_lengthMm;
    double m_widthMm;
    double m_heightMm;
    QString m_girdle;
    QString m_culet;
    QString m_certificateNumber;
    QString m_certificateLab;
    QString m_certificateDate;
    QString m_certificateUrl;
    QString m_certificateNotes;
    qint64 m_purchasePriceCents;
    qint64 m_sellingPriceCents;
    qint64 m_discountPriceCents;
    qint64 m_minSellingPriceCents;
    QString m_status;
    QString m_location;
    QString m_locationDetails;
    qint64 m_supplierId;
    QString m_supplierName;
    bool m_isFavorite;
    bool m_archived;
    QString m_createdAt;
    QString m_updatedAt;
    QString m_mainImageThumbnail;
    QString m_mainImageFile;
    int m_imageCount;
};

#endif
