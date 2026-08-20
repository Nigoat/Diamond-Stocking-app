#include "DiamondRepository.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <cmath>

static Diamond parseDiamondRow(const QSqlQuery &q) {
    Diamond d;
    d.setId(q.value(0).toLongLong());
    d.setReference(q.value(1).toString());
    d.setSku(q.value(2).toString());
    d.setBarcode(q.value(3).toString());
    d.setName(q.value(4).toString());
    d.setDescription(q.value(5).toString());
    d.setShape(q.value(6).toString());
    d.setCartWeight(q.value(7).toDouble());
    d.setColor(q.value(8).toString());
    d.setClarity(q.value(9).toString());
    d.setCut(q.value(10).toString());
    d.setPolish(q.value(11).toString());
    d.setSymmetry(q.value(12).toString());
    d.setFluorescence(q.value(13).toString());
    d.setFluorescenceColor(q.value(14).toString());
    d.setTablePercentage(q.value(15).toDouble());
    d.setDepthPercentage(q.value(16).toDouble());
    d.setLengthMm(q.value(17).toDouble());
    d.setWidthMm(q.value(18).toDouble());
    d.setHeightMm(q.value(19).toDouble());
    d.setGirdle(q.value(20).toString());
    d.setCulet(q.value(21).toString());
    d.setCertificateNumber(q.value(22).toString());
    d.setCertificateLab(q.value(23).toString());
    d.setCertificateDate(q.value(24).toString());
    d.setCertificateUrl(q.value(25).toString());
    d.setCertificateNotes(q.value(26).toString());
    d.setPurchasePriceCents(q.value(27).toLongLong());
    d.setSellingPriceCents(q.value(28).toLongLong());
    d.setDiscountPriceCents(q.value(29).toLongLong());
    d.setMinSellingPriceCents(q.value(30).toLongLong());
    d.setStatus(q.value(31).toString());
    d.setLocation(q.value(32).toString());
    d.setLocationDetails(q.value(33).toString());
    d.setSupplierId(q.value(34).toLongLong());
    d.setIsFavorite(q.value(35).toInt() != 0);
    d.setArchived(q.value(36).toInt() != 0);
    d.setCreatedAt(q.value(37).toString());
    d.setUpdatedAt(q.value(38).toString());
    d.setSupplierName(q.value(39).toString());
    d.setMainImageThumbnail(q.value(40).toString());
    d.setMainImageFile(q.value(41).toString());
    d.setImageCount(q.value(42).toInt());
    return d;
}

QList<Diamond> DiamondRepository::getList(const DiamondFilterCriteria &criteria) {
    QList<Diamond> list;
    if (!DatabaseManager::instance().isOpen()) return list;

    QString sql = QStringLiteral(
        "SELECT d.id, d.reference, d.sku, d.barcode, d.name, d.description, d.shape, d.carat_weight, "
        "d.color, d.clarity, d.cut, d.polish, d.symmetry, d.fluorescence, d.fluorescence_color, "
        "d.table_percentage, d.depth_percentage, d.length_mm, d.width_mm, d.height_mm, d.girdle, d.culet, "
        "d.certificate_number, d.certificate_lab, d.certificate_date, d.certificate_url, d.certificate_notes, "
        "d.purchase_price_cents, d.selling_price_cents, d.discount_price_cents, d.min_selling_price_cents, "
        "d.status, d.location, d.location_details, d.supplier_id, d.is_favorite, d.archived, "
        "d.created_at, d.updated_at, "
        "s.name AS supplier_name, "
        "(SELECT img.thumbnail_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_thumb, "
        "(SELECT img.file_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_file, "
        "(SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = d.id) AS image_count "
        "FROM diamonds d "
        "LEFT JOIN suppliers s ON s.id = d.supplier_id "
        "WHERE 1=1 "
    );

    if (!criteria.includeArchived) {
        sql += QStringLiteral("AND d.archived = 0 ");
    }

    if (!criteria.search.trimmed().isEmpty()) {
        const QStringList tokens = criteria.search.trimmed().split(QLatin1Char(' '), Qt::SkipEmptyParts);
        for (int i = 0; i < tokens.size(); ++i) {
            sql += QStringLiteral(
                "AND (d.reference LIKE :search_%1 OR d.name LIKE :search_%1 OR d.sku LIKE :search_%1 "
                "OR d.barcode LIKE :search_%1 OR d.certificate_number LIKE :search_%1 OR d.description LIKE :search_%1 "
                "OR d.shape LIKE :search_%1 OR d.color LIKE :search_%1 OR d.clarity LIKE :search_%1 "
                "OR s.name LIKE :search_%1 OR s.company LIKE :search_%1) "
            ).arg(i);
        }
    }

    if (!criteria.reference.trimmed().isEmpty()) {
        sql += QStringLiteral("AND d.reference LIKE :ref ");
    }
    if (!criteria.name.trimmed().isEmpty()) {
        sql += QStringLiteral("AND d.name LIKE :name_filter ");
    }
    if (!criteria.status.isEmpty() && criteria.status != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.status = :status ");
    }
    if (!criteria.shape.isEmpty() && criteria.shape != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.shape = :shape ");
    }
    if (!criteria.color.isEmpty() && criteria.color != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.color = :color ");
    }
    if (!criteria.clarity.isEmpty() && criteria.clarity != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.clarity = :clarity ");
    }
    if (!criteria.cut.isEmpty() && criteria.cut != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.cut = :cut ");
    }
    if (!criteria.certificateLab.isEmpty() && criteria.certificateLab != QStringLiteral("All")) {
        sql += QStringLiteral("AND d.certificate_lab = :cert_lab ");
    }
    if (criteria.minCarat > 0.0) {
        sql += QStringLiteral("AND d.carat_weight >= :min_carat ");
    }
    if (criteria.maxCarat < 900.0) {
        sql += QStringLiteral("AND d.carat_weight <= :max_carat ");
    }
    if (criteria.minPriceCents > 0) {
        sql += QStringLiteral("AND d.selling_price_cents >= :min_price ");
    }
    if (criteria.maxPriceCents < 900000000000) {
        sql += QStringLiteral("AND d.selling_price_cents <= :max_price ");
    }
    if (criteria.supplierId > 0) {
        sql += QStringLiteral("AND d.supplier_id = :supplier_id ");
    }
    if (criteria.isFavorite >= 0) {
        sql += QStringLiteral("AND d.is_favorite = :is_favorite ");
    }
    if (criteria.hasImage == 1) {
        sql += QStringLiteral("AND (SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = d.id) > 0 ");
    } else if (criteria.hasImage == 2) {
        sql += QStringLiteral("AND (SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = d.id) = 0 ");
    }
    if (criteria.hasCertificate == 1) {
        sql += QStringLiteral("AND (d.certificate_number IS NOT NULL AND length(trim(d.certificate_number)) > 0) ");
    } else if (criteria.hasCertificate == 2) {
        sql += QStringLiteral("AND (d.certificate_number IS NULL OR length(trim(d.certificate_number)) = 0) ");
    }

    QString sortCol = QStringLiteral("d.created_at");
    if (criteria.sortBy == QStringLiteral("reference")) sortCol = QStringLiteral("d.reference");
    else if (criteria.sortBy == QStringLiteral("name")) sortCol = QStringLiteral("d.name");
    else if (criteria.sortBy == QStringLiteral("carat")) sortCol = QStringLiteral("d.carat_weight");
    else if (criteria.sortBy == QStringLiteral("price")) sortCol = QStringLiteral("d.selling_price_cents");
    else if (criteria.sortBy == QStringLiteral("purchase_price")) sortCol = QStringLiteral("d.purchase_price_cents");
    else if (criteria.sortBy == QStringLiteral("color")) sortCol = QStringLiteral("d.color");
    else if (criteria.sortBy == QStringLiteral("clarity")) sortCol = QStringLiteral("d.clarity");
    else if (criteria.sortBy == QStringLiteral("status")) sortCol = QStringLiteral("d.status");
    else if (criteria.sortBy == QStringLiteral("updated_at")) sortCol = QStringLiteral("d.updated_at");

    sql += QStringLiteral("ORDER BY %1 %2").arg(sortCol, criteria.sortAscending ? QStringLiteral("ASC") : QStringLiteral("DESC"));

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(sql);

    if (!criteria.search.trimmed().isEmpty()) {
        const QStringList tokens = criteria.search.trimmed().split(QLatin1Char(' '), Qt::SkipEmptyParts);
        for (int i = 0; i < tokens.size(); ++i) {
            q.bindValue(QStringLiteral(":search_%1").arg(i), QStringLiteral("%%1%").arg(tokens[i]));
        }
    }
    if (!criteria.reference.trimmed().isEmpty()) {
        q.bindValue(QStringLiteral(":ref"), QStringLiteral("%%1%").arg(criteria.reference.trimmed()));
    }
    if (!criteria.name.trimmed().isEmpty()) {
        q.bindValue(QStringLiteral(":name_filter"), QStringLiteral("%%1%").arg(criteria.name.trimmed()));
    }
    if (!criteria.status.isEmpty() && criteria.status != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":status"), criteria.status);
    }
    if (!criteria.shape.isEmpty() && criteria.shape != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":shape"), criteria.shape);
    }
    if (!criteria.color.isEmpty() && criteria.color != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":color"), criteria.color);
    }
    if (!criteria.clarity.isEmpty() && criteria.clarity != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":clarity"), criteria.clarity);
    }
    if (!criteria.cut.isEmpty() && criteria.cut != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":cut"), criteria.cut);
    }
    if (!criteria.certificateLab.isEmpty() && criteria.certificateLab != QStringLiteral("All")) {
        q.bindValue(QStringLiteral(":cert_lab"), criteria.certificateLab);
    }
    if (criteria.minCarat > 0.0) {
        q.bindValue(QStringLiteral(":min_carat"), criteria.minCarat);
    }
    if (criteria.maxCarat < 900.0) {
        q.bindValue(QStringLiteral(":max_carat"), criteria.maxCarat);
    }
    if (criteria.minPriceCents > 0) {
        q.bindValue(QStringLiteral(":min_price"), criteria.minPriceCents);
    }
    if (criteria.maxPriceCents < 900000000000) {
        q.bindValue(QStringLiteral(":max_price"), criteria.maxPriceCents);
    }
    if (criteria.supplierId > 0) {
        q.bindValue(QStringLiteral(":supplier_id"), criteria.supplierId);
    }
    if (criteria.isFavorite >= 0) {
        q.bindValue(QStringLiteral(":is_favorite"), criteria.isFavorite);
    }

    if (q.exec()) {
        while (q.next()) {
            list.append(parseDiamondRow(q));
        }
    }
    return list;
}

std::optional<Diamond> DiamondRepository::getById(qint64 id) {
    if (!DatabaseManager::instance().isOpen()) return std::nullopt;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "SELECT d.id, d.reference, d.sku, d.barcode, d.name, d.description, d.shape, d.carat_weight, "
        "d.color, d.clarity, d.cut, d.polish, d.symmetry, d.fluorescence, d.fluorescence_color, "
        "d.table_percentage, d.depth_percentage, d.length_mm, d.width_mm, d.height_mm, d.girdle, d.culet, "
        "d.certificate_number, d.certificate_lab, d.certificate_date, d.certificate_url, d.certificate_notes, "
        "d.purchase_price_cents, d.selling_price_cents, d.discount_price_cents, d.min_selling_price_cents, "
        "d.status, d.location, d.location_details, d.supplier_id, d.is_favorite, d.archived, "
        "d.created_at, d.updated_at, "
        "s.name AS supplier_name, "
        "(SELECT img.thumbnail_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_thumb, "
        "(SELECT img.file_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_file, "
        "(SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = d.id) AS image_count "
        "FROM diamonds d "
        "LEFT JOIN suppliers s ON s.id = d.supplier_id "
        "WHERE d.id = :id"
    ));
    q.bindValue(QStringLiteral(":id"), id);

    if (q.exec() && q.next()) {
        return parseDiamondRow(q);
    }
    return std::nullopt;
}

std::optional<Diamond> DiamondRepository::getByReference(const QString &reference) {
    if (!DatabaseManager::instance().isOpen()) return std::nullopt;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "SELECT d.id, d.reference, d.sku, d.barcode, d.name, d.description, d.shape, d.carat_weight, "
        "d.color, d.clarity, d.cut, d.polish, d.symmetry, d.fluorescence, d.fluorescence_color, "
        "d.table_percentage, d.depth_percentage, d.length_mm, d.width_mm, d.height_mm, d.girdle, d.culet, "
        "d.certificate_number, d.certificate_lab, d.certificate_date, d.certificate_url, d.certificate_notes, "
        "d.purchase_price_cents, d.selling_price_cents, d.discount_price_cents, d.min_selling_price_cents, "
        "d.status, d.location, d.location_details, d.supplier_id, d.is_favorite, d.archived, "
        "d.created_at, d.updated_at, "
        "s.name AS supplier_name, "
        "(SELECT img.thumbnail_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_thumb, "
        "(SELECT img.file_path FROM diamond_images img WHERE img.diamond_id = d.id ORDER BY (img.image_type = 'main') DESC, img.sort_order ASC, img.id ASC LIMIT 1) AS main_image_file, "
        "(SELECT COUNT(*) FROM diamond_images img WHERE img.diamond_id = d.id) AS image_count "
        "FROM diamonds d "
        "LEFT JOIN suppliers s ON s.id = d.supplier_id "
        "WHERE d.reference = :ref"
    ));
    q.bindValue(QStringLiteral(":ref"), reference.trimmed());

    if (q.exec() && q.next()) {
        return parseDiamondRow(q);
    }
    return std::nullopt;
}

bool DiamondRepository::referenceExists(const QString &reference, qint64 excludeId) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("SELECT COUNT(*) FROM diamonds WHERE reference = :ref AND id != :exclude_id"));
    q.bindValue(QStringLiteral(":ref"), reference.trimmed());
    q.bindValue(QStringLiteral(":exclude_id"), excludeId);

    if (q.exec() && q.next()) {
        return q.value(0).toInt() > 0;
    }
    return false;
}

bool DiamondRepository::insert(Diamond &diamond, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    if (referenceExists(diamond.reference())) {
        if (errorMessage) *errorMessage = QStringLiteral("Reference already exists.");
        return false;
    }

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO diamonds ("
        "reference, sku, barcode, name, description, shape, carat_weight, color, clarity, cut, polish, symmetry, fluorescence, fluorescence_color,"
        "table_percentage, depth_percentage, length_mm, width_mm, height_mm, girdle, culet,"
        "certificate_number, certificate_lab, certificate_date, certificate_url, certificate_notes,"
        "purchase_price_cents, selling_price_cents, discount_price_cents, min_selling_price_cents,"
        "status, location, location_details, supplier_id, is_favorite, archived, created_at, updated_at"
        ") VALUES ("
        ":reference, :sku, :barcode, :name, :description, :shape, :carat_weight, :color, :clarity, :cut, :polish, :symmetry, :fluorescence, :fluorescence_color,"
        ":table_percentage, :depth_percentage, :length_mm, :width_mm, :height_mm, :girdle, :culet,"
        ":certificate_number, :certificate_lab, :certificate_date, :certificate_url, :certificate_notes,"
        ":purchase_price_cents, :selling_price_cents, :discount_price_cents, :min_selling_price_cents,"
        ":status, :location, :location_details, :supplier_id, :is_favorite, :archived, datetime('now', 'utc'), datetime('now', 'utc')"
        ")"
    ));

    q.bindValue(QStringLiteral(":reference"), diamond.reference().trimmed());
    q.bindValue(QStringLiteral(":sku"), diamond.sku().trimmed());
    q.bindValue(QStringLiteral(":barcode"), diamond.barcode().trimmed());
    q.bindValue(QStringLiteral(":name"), diamond.name().trimmed());
    q.bindValue(QStringLiteral(":description"), diamond.description().trimmed());
    q.bindValue(QStringLiteral(":shape"), diamond.shape());
    q.bindValue(QStringLiteral(":carat_weight"), diamond.caratWeight());
    q.bindValue(QStringLiteral(":color"), diamond.color());
    q.bindValue(QStringLiteral(":clarity"), diamond.clarity());
    q.bindValue(QStringLiteral(":cut"), diamond.cut());
    q.bindValue(QStringLiteral(":polish"), diamond.polish());
    q.bindValue(QStringLiteral(":symmetry"), diamond.symmetry());
    q.bindValue(QStringLiteral(":fluorescence"), diamond.fluorescence());
    q.bindValue(QStringLiteral(":fluorescence_color"), diamond.fluorescenceColor());
    q.bindValue(QStringLiteral(":table_percentage"), diamond.tablePercentage());
    q.bindValue(QStringLiteral(":depth_percentage"), diamond.depthPercentage());
    q.bindValue(QStringLiteral(":length_mm"), diamond.lengthMm());
    q.bindValue(QStringLiteral(":width_mm"), diamond.widthMm());
    q.bindValue(QStringLiteral(":height_mm"), diamond.heightMm());
    q.bindValue(QStringLiteral(":girdle"), diamond.girdle());
    q.bindValue(QStringLiteral(":culet"), diamond.culet());
    q.bindValue(QStringLiteral(":certificate_number"), diamond.certificateNumber().trimmed());
    q.bindValue(QStringLiteral(":certificate_lab"), diamond.certificateLab());
    q.bindValue(QStringLiteral(":certificate_date"), diamond.certificateDate());
    q.bindValue(QStringLiteral(":certificate_url"), diamond.certificateUrl());
    q.bindValue(QStringLiteral(":certificate_notes"), diamond.certificateNotes());
    q.bindValue(QStringLiteral(":purchase_price_cents"), diamond.purchasePriceCents());
    q.bindValue(QStringLiteral(":selling_price_cents"), diamond.sellingPriceCents());
    q.bindValue(QStringLiteral(":discount_price_cents"), diamond.discountPriceCents());
    q.bindValue(QStringLiteral(":min_selling_price_cents"), diamond.minSellingPriceCents());
    q.bindValue(QStringLiteral(":status"), diamond.status());
    q.bindValue(QStringLiteral(":location"), diamond.location());
    q.bindValue(QStringLiteral(":location_details"), diamond.locationDetails());
    if (diamond.supplierId() > 0) {
        q.bindValue(QStringLiteral(":supplier_id"), diamond.supplierId());
    } else {
        q.bindValue(QStringLiteral(":supplier_id"), QVariant());
    }
    q.bindValue(QStringLiteral(":is_favorite"), diamond.isFavorite() ? 1 : 0);
    q.bindValue(QStringLiteral(":archived"), diamond.archived() ? 1 : 0);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }

    diamond.setId(q.lastInsertId().toLongLong());
    return true;
}

bool DiamondRepository::update(const Diamond &diamond, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    if (referenceExists(diamond.reference(), diamond.id())) {
        if (errorMessage) *errorMessage = QStringLiteral("Reference already in use by another diamond.");
        return false;
    }

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "UPDATE diamonds SET "
        "reference = :reference, sku = :sku, barcode = :barcode, name = :name, description = :description, "
        "shape = :shape, carat_weight = :carat_weight, color = :color, clarity = :clarity, cut = :cut, "
        "polish = :polish, symmetry = :symmetry, fluorescence = :fluorescence, fluorescence_color = :fluorescence_color, "
        "table_percentage = :table_percentage, depth_percentage = :depth_percentage, "
        "length_mm = :length_mm, width_mm = :width_mm, height_mm = :height_mm, girdle = :girdle, culet = :culet, "
        "certificate_number = :certificate_number, certificate_lab = :certificate_lab, certificate_date = :certificate_date, "
        "certificate_url = :certificate_url, certificate_notes = :certificate_notes, "
        "purchase_price_cents = :purchase_price_cents, selling_price_cents = :selling_price_cents, "
        "discount_price_cents = :discount_price_cents, min_selling_price_cents = :min_selling_price_cents, "
        "status = :status, location = :location, location_details = :location_details, supplier_id = :supplier_id, "
        "is_favorite = :is_favorite, archived = :archived, updated_at = datetime('now', 'utc') "
        "WHERE id = :id"
    ));

    q.bindValue(QStringLiteral(":id"), diamond.id());
    q.bindValue(QStringLiteral(":reference"), diamond.reference().trimmed());
    q.bindValue(QStringLiteral(":sku"), diamond.sku().trimmed());
    q.bindValue(QStringLiteral(":barcode"), diamond.barcode().trimmed());
    q.bindValue(QStringLiteral(":name"), diamond.name().trimmed());
    q.bindValue(QStringLiteral(":description"), diamond.description().trimmed());
    q.bindValue(QStringLiteral(":shape"), diamond.shape());
    q.bindValue(QStringLiteral(":carat_weight"), diamond.caratWeight());
    q.bindValue(QStringLiteral(":color"), diamond.color());
    q.bindValue(QStringLiteral(":clarity"), diamond.clarity());
    q.bindValue(QStringLiteral(":cut"), diamond.cut());
    q.bindValue(QStringLiteral(":polish"), diamond.polish());
    q.bindValue(QStringLiteral(":symmetry"), diamond.symmetry());
    q.bindValue(QStringLiteral(":fluorescence"), diamond.fluorescence());
    q.bindValue(QStringLiteral(":fluorescence_color"), diamond.fluorescenceColor());
    q.bindValue(QStringLiteral(":table_percentage"), diamond.tablePercentage());
    q.bindValue(QStringLiteral(":depth_percentage"), diamond.depthPercentage());
    q.bindValue(QStringLiteral(":length_mm"), diamond.lengthMm());
    q.bindValue(QStringLiteral(":width_mm"), diamond.widthMm());
    q.bindValue(QStringLiteral(":height_mm"), diamond.heightMm());
    q.bindValue(QStringLiteral(":girdle"), diamond.girdle());
    q.bindValue(QStringLiteral(":culet"), diamond.culet());
    q.bindValue(QStringLiteral(":certificate_number"), diamond.certificateNumber().trimmed());
    q.bindValue(QStringLiteral(":certificate_lab"), diamond.certificateLab());
    q.bindValue(QStringLiteral(":certificate_date"), diamond.certificateDate());
    q.bindValue(QStringLiteral(":certificate_url"), diamond.certificateUrl());
    q.bindValue(QStringLiteral(":certificate_notes"), diamond.certificateNotes());
    q.bindValue(QStringLiteral(":purchase_price_cents"), diamond.purchasePriceCents());
    q.bindValue(QStringLiteral(":selling_price_cents"), diamond.sellingPriceCents());
    q.bindValue(QStringLiteral(":discount_price_cents"), diamond.discountPriceCents());
    q.bindValue(QStringLiteral(":min_selling_price_cents"), diamond.minSellingPriceCents());
    q.bindValue(QStringLiteral(":status"), diamond.status());
    q.bindValue(QStringLiteral(":location"), diamond.location());
    q.bindValue(QStringLiteral(":location_details"), diamond.locationDetails());
    if (diamond.supplierId() > 0) {
        q.bindValue(QStringLiteral(":supplier_id"), diamond.supplierId());
    } else {
        q.bindValue(QStringLiteral(":supplier_id"), QVariant());
    }
    q.bindValue(QStringLiteral(":is_favorite"), diamond.isFavorite() ? 1 : 0);
    q.bindValue(QStringLiteral(":archived"), diamond.archived() ? 1 : 0);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::setArchived(qint64 id, bool archived, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("UPDATE diamonds SET archived = :archived, updated_at = datetime('now', 'utc') WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":archived"), archived ? 1 : 0);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::setFavorite(qint64 id, bool favorite, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("UPDATE diamonds SET is_favorite = :is_fav, updated_at = datetime('now', 'utc') WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":is_fav"), favorite ? 1 : 0);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::setStatus(qint64 id, const QString &status, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("UPDATE diamonds SET status = :status, updated_at = datetime('now', 'utc') WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);
    q.bindValue(QStringLiteral(":status"), status);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::deletePermanently(qint64 id, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM diamonds WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), id);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::bulkUpdateStatus(const QList<qint64> &ids, const QString &status, QString *errorMessage) {
    if (ids.isEmpty() || !DatabaseManager::instance().isOpen()) return true;

    DatabaseManager::instance().beginTransaction();
    for (qint64 id : ids) {
        QSqlQuery q(DatabaseManager::instance().database());
        q.prepare(QStringLiteral("UPDATE diamonds SET status = :status, updated_at = datetime('now', 'utc') WHERE id = :id"));
        q.bindValue(QStringLiteral(":id"), id);
        q.bindValue(QStringLiteral(":status"), status);
        if (!q.exec()) {
            if (errorMessage) *errorMessage = q.lastError().text();
            DatabaseManager::instance().rollbackTransaction();
            return false;
        }
    }
    DatabaseManager::instance().commitTransaction();
    return true;
}

bool DiamondRepository::bulkAdjustSellingPricePercent(const QList<qint64> &ids, double percent, QString *errorMessage) {
    if (ids.isEmpty() || !DatabaseManager::instance().isOpen()) return true;

    double factor = 1.0 + (percent / 100.0);
    if (factor < 0.0) factor = 0.0;

    DatabaseManager::instance().beginTransaction();
    for (qint64 id : ids) {
        QSqlQuery fetch(DatabaseManager::instance().database());
        fetch.prepare(QStringLiteral("SELECT selling_price_cents FROM diamonds WHERE id = :id"));
        fetch.bindValue(QStringLiteral(":id"), id);
        if (fetch.exec() && fetch.next()) {
            qint64 curCents = fetch.value(0).toLongLong();
            qint64 newCents = static_cast<qint64>(std::round(static_cast<double>(curCents) * factor));

            QSqlQuery update(DatabaseManager::instance().database());
            update.prepare(QStringLiteral("UPDATE diamonds SET selling_price_cents = :new_cents, updated_at = datetime('now', 'utc') WHERE id = :id"));
            update.bindValue(QStringLiteral(":new_cents"), newCents);
            update.bindValue(QStringLiteral(":id"), id);
            if (!update.exec()) {
                if (errorMessage) *errorMessage = update.lastError().text();
                DatabaseManager::instance().rollbackTransaction();
                return false;
            }
        }
    }
    DatabaseManager::instance().commitTransaction();
    return true;
}

bool DiamondRepository::bulkArchive(const QList<qint64> &ids, bool archive, QString *errorMessage) {
    if (ids.isEmpty() || !DatabaseManager::instance().isOpen()) return true;

    DatabaseManager::instance().beginTransaction();
    for (qint64 id : ids) {
        QSqlQuery q(DatabaseManager::instance().database());
        q.prepare(QStringLiteral("UPDATE diamonds SET archived = :archived, updated_at = datetime('now', 'utc') WHERE id = :id"));
        q.bindValue(QStringLiteral(":id"), id);
        q.bindValue(QStringLiteral(":archived"), archive ? 1 : 0);
        if (!q.exec()) {
            if (errorMessage) *errorMessage = q.lastError().text();
            DatabaseManager::instance().rollbackTransaction();
            return false;
        }
    }
    DatabaseManager::instance().commitTransaction();
    return true;
}

QList<DiamondImage> DiamondRepository::getImages(qint64 diamondId) {
    QList<DiamondImage> list;
    if (!DatabaseManager::instance().isOpen()) return list;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "SELECT id, diamond_id, file_path, thumbnail_path, image_type, sort_order, created_at "
        "FROM diamond_images WHERE diamond_id = :diamond_id "
        "ORDER BY (image_type = 'main') DESC, sort_order ASC, id ASC"
    ));
    q.bindValue(QStringLiteral(":diamond_id"), diamondId);

    if (q.exec()) {
        while (q.next()) {
            DiamondImage img;
            img.setId(q.value(0).toLongLong());
            img.setDiamondId(q.value(1).toLongLong());
            img.setFilePath(q.value(2).toString());
            img.setThumbnailPath(q.value(3).toString());
            img.setImageType(q.value(4).toString());
            img.setSortOrder(q.value(5).toInt());
            img.setCreatedAt(q.value(6).toString());
            list.append(img);
        }
    }
    return list;
}

bool DiamondRepository::insertImage(DiamondImage &image, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral(
        "INSERT INTO diamond_images (diamond_id, file_path, thumbnail_path, image_type, sort_order, created_at) "
        "VALUES (:diamond_id, :file_path, :thumbnail_path, :image_type, :sort_order, datetime('now', 'utc'))"
    ));
    q.bindValue(QStringLiteral(":diamond_id"), image.diamondId());
    q.bindValue(QStringLiteral(":file_path"), image.filePath());
    q.bindValue(QStringLiteral(":thumbnail_path"), image.thumbnailPath());
    q.bindValue(QStringLiteral(":image_type"), image.imageType());
    q.bindValue(QStringLiteral(":sort_order"), image.sortOrder());

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }

    image.setId(q.lastInsertId().toLongLong());
    return true;
}

bool DiamondRepository::deleteImage(qint64 imageId, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    QSqlQuery q(DatabaseManager::instance().database());
    q.prepare(QStringLiteral("DELETE FROM diamond_images WHERE id = :id"));
    q.bindValue(QStringLiteral(":id"), imageId);

    if (!q.exec()) {
        if (errorMessage) *errorMessage = q.lastError().text();
        return false;
    }
    return true;
}

bool DiamondRepository::setMainImage(qint64 diamondId, qint64 imageId, QString *errorMessage) {
    if (!DatabaseManager::instance().isOpen()) return false;

    DatabaseManager::instance().beginTransaction();
    QSqlQuery q1(DatabaseManager::instance().database());
    q1.prepare(QStringLiteral("UPDATE diamond_images SET image_type = 'side' WHERE diamond_id = :diamond_id"));
    q1.bindValue(QStringLiteral(":diamond_id"), diamondId);
    if (!q1.exec()) {
        if (errorMessage) *errorMessage = q1.lastError().text();
        DatabaseManager::instance().rollbackTransaction();
        return false;
    }

    QSqlQuery q2(DatabaseManager::instance().database());
    q2.prepare(QStringLiteral("UPDATE diamond_images SET image_type = 'main' WHERE id = :id AND diamond_id = :diamond_id"));
    q2.bindValue(QStringLiteral(":id"), imageId);
    q2.bindValue(QStringLiteral(":diamond_id"), diamondId);
    if (!q2.exec()) {
        if (errorMessage) *errorMessage = q2.lastError().text();
        DatabaseManager::instance().rollbackTransaction();
        return false;
    }

    DatabaseManager::instance().commitTransaction();
    return true;
}
