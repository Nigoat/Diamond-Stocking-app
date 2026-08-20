#include "PrintService.h"
#include "DiamondRepository.h"
#include "AppSettings.h"
#include "DateUtils.h"
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QFont>
#include <QImage>
#include <QFileInfo>
#include <QUrl>

PrintService &PrintService::instance() {
    static PrintService inst;
    return inst;
}

bool PrintService::printDiamondSpecSheet(qint64 diamondId, const QString &outputPath, QString *errorMessage) {
    DiamondRepository repo;
    auto opt = repo.getById(diamondId);
    if (!opt.has_value()) {
        if (errorMessage) *errorMessage = QStringLiteral("Diamond not found.");
        return false;
    }

    Diamond d = opt.value();

    QString cleanPath = outputPath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(outputPath).toLocalFile();
    }

    QPdfWriter writer(cleanPath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Portrait);
    writer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        if (errorMessage) *errorMessage = QStringLiteral("Failed to initialize PDF writer: %1").arg(cleanPath);
        return false;
    }

    QFont titleFont(QStringLiteral("sans-serif"), 16, QFont::Bold);
    QFont subTitleFont(QStringLiteral("sans-serif"), 10);
    QFont sectionFont(QStringLiteral("sans-serif"), 11, QFont::Bold);
    QFont labelFont(QStringLiteral("sans-serif"), 9, QFont::Bold);
    QFont valFont(QStringLiteral("sans-serif"), 9);
    QFont priceFont(QStringLiteral("sans-serif"), 14, QFont::Bold);

    int y = 250;
    painter.setFont(titleFont);
    painter.setPen(QColor(15, 23, 42));
    painter.drawText(200, y, AppSettings::instance().storeName().toUpper());

    y += 180;
    painter.setFont(subTitleFont);
    painter.setPen(QColor(100, 116, 139));
    painter.drawText(200, y, QStringLiteral("DIAMOND SPECIFICATION SHEET & CERTIFICATE DOSSIER"));

    y += 100;
    painter.setPen(QPen(QColor(226, 232, 240), 8));
    painter.drawLine(200, y, 7000, y);
    y += 250;

    int leftColX = 200;
    int rightColX = 3800;

    if (!d.mainImageFile().isEmpty() && QFile::exists(d.mainImageFile())) {
        QImage img(d.mainImageFile());
        if (!img.isNull()) {
            QImage scaled = img.scaled(3200, 2400, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            painter.drawImage(leftColX, y, scaled);
        }
    } else {
        painter.fillRect(leftColX, y, 3200, 2200, QColor(241, 245, 249));
        painter.setFont(subTitleFont);
        painter.setPen(QColor(148, 163, 184));
        painter.drawText(QRect(leftColX, y, 3200, 2200), Qt::AlignCenter, QStringLiteral("No Image Available"));
    }

    int ry = y;
    painter.setFont(titleFont);
    painter.setPen(QColor(15, 23, 42));
    painter.drawText(rightColX, ry, d.reference());

    ry += 200;
    painter.setFont(subTitleFont);
    painter.setPen(QColor(71, 85, 105));
    painter.drawText(rightColX, ry, d.name());

    ry += 250;
    painter.fillRect(rightColX, ry - 60, 3200, 320, QColor(238, 242, 255));
    painter.setFont(priceFont);
    painter.setPen(QColor(79, 70, 229));
    painter.drawText(rightColX + 150, ry + 140, QStringLiteral("Selling Price: %1").arg(d.sellingPrice().formatted()));

    ry += 450;
    painter.setFont(sectionFont);
    painter.setPen(QColor(30, 41, 59));
    painter.drawText(rightColX, ry, QStringLiteral("Key Characteristics"));
    ry += 80;
    painter.setPen(QPen(QColor(203, 213, 225), 4));
    painter.drawLine(rightColX, ry, rightColX + 3200, ry);
    ry += 180;

    auto drawRow = [&](int x, int &curY, const QString &label, const QString &val) {
        painter.setFont(labelFont);
        painter.setPen(QColor(100, 116, 139));
        painter.drawText(x, curY, label);
        painter.setFont(valFont);
        painter.setPen(QColor(15, 23, 42));
        painter.drawText(x + 1400, curY, val);
        curY += 160;
    };

    drawRow(rightColX, ry, QStringLiteral("Shape:"), d.shape());
    drawRow(rightColX, ry, QStringLiteral("Carat Weight:"), QString::number(d.caratWeight(), 'f', 2) + QStringLiteral(" ct"));
    drawRow(rightColX, ry, QStringLiteral("Color Grade:"), d.color());
    drawRow(rightColX, ry, QStringLiteral("Clarity Grade:"), d.clarity());
    drawRow(rightColX, ry, QStringLiteral("Cut Grade:"), d.cut());
    drawRow(rightColX, ry, QStringLiteral("Status:"), d.status());

    y = std::max(y + 2400, ry + 150);

    painter.setFont(sectionFont);
    painter.setPen(QColor(30, 41, 59));
    painter.drawText(200, y, QStringLiteral("Technical Specifications & Grading"));
    y += 80;
    painter.setPen(QPen(QColor(203, 213, 225), 4));
    painter.drawLine(200, y, 7000, y);
    y += 180;

    int leftY = y;
    int rightY = y;

    drawRow(leftColX, leftY, QStringLiteral("Polish:"), d.polish());
    drawRow(leftColX, leftY, QStringLiteral("Symmetry:"), d.symmetry());
    drawRow(leftColX, leftY, QStringLiteral("Fluorescence:"), d.fluorescence());
    drawRow(leftColX, leftY, QStringLiteral("Table %:"), QString::number(d.tablePercentage(), 'f', 1) + QStringLiteral(" %"));
    drawRow(leftColX, leftY, QStringLiteral("Depth %:"), QString::number(d.depthPercentage(), 'f', 1) + QStringLiteral(" %"));

    drawRow(rightColX, rightY, QStringLiteral("Measurements:"), d.measurementsFormatted());
    drawRow(rightColX, rightY, QStringLiteral("Girdle:"), d.girdle().isEmpty() ? QStringLiteral("-") : d.girdle());
    drawRow(rightColX, rightY, QStringLiteral("Culet:"), d.culet().isEmpty() ? QStringLiteral("-") : d.culet());
    drawRow(rightColX, rightY, QStringLiteral("SKU / Barcode:"), d.sku().isEmpty() ? d.barcode() : d.sku());
    drawRow(rightColX, rightY, QStringLiteral("Stock Location:"), d.location() + (d.locationDetails().isEmpty() ? QString() : QStringLiteral(" (%1)").arg(d.locationDetails())));

    y = std::max(leftY, rightY) + 150;

    painter.setFont(sectionFont);
    painter.setPen(QColor(30, 41, 59));
    painter.drawText(200, y, QStringLiteral("Grading Laboratory & Certificate"));
    y += 80;
    painter.setPen(QPen(QColor(203, 213, 225), 4));
    painter.drawLine(200, y, 7000, y);
    y += 180;

    leftY = y;
    drawRow(leftColX, leftY, QStringLiteral("Lab Name:"), d.certificateLab());
    drawRow(leftColX, leftY, QStringLiteral("Certificate Number:"), d.certificateNumber().isEmpty() ? QStringLiteral("None") : d.certificateNumber());
    drawRow(leftColX, leftY, QStringLiteral("Certificate Date:"), DateUtils::formatDisplayDate(d.certificateDate()));

    if (!d.certificateNotes().isEmpty()) {
        leftY += 50;
        painter.setFont(labelFont);
        painter.setPen(QColor(100, 116, 139));
        painter.drawText(leftColX, leftY, QStringLiteral("Certificate Notes:"));
        leftY += 120;
        painter.setFont(valFont);
        painter.setPen(QColor(51, 65, 85));
        painter.drawText(QRect(leftColX, leftY, 6800, 400), Qt::TextWordWrap, d.certificateNotes());
    }

    painter.setFont(subTitleFont);
    painter.setPen(QColor(148, 163, 184));
    painter.drawText(200, 9600, QStringLiteral("Official Inventory Record - %1 - Generated %2").arg(
        AppSettings::instance().storeName(),
        DateUtils::formatDisplayDateTime(DateUtils::currentUtcIsoString())
    ));

    painter.end();
    return true;
}
