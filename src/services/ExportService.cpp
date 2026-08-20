#include "ExportService.h"
#include "DiamondRepository.h"
#include "AppSettings.h"
#include <QFile>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QDateTime>
#include <QFont>
#include <QUrl>

ExportService &ExportService::instance() {
    static ExportService inst;
    return inst;
}

static QString escapeCsvField(const QString &field) {
    QString res = field;
    if (res.contains(QLatin1Char(',')) || res.contains(QLatin1Char('"')) || res.contains(QLatin1Char('\n')) || res.contains(QLatin1Char('\r'))) {
        res.replace(QStringLiteral("\""), QStringLiteral("\"\""));
        return QStringLiteral("\"%1\"").arg(res);
    }
    return res;
}

bool ExportService::exportToCsv(const QString &filePath, const DiamondFilterCriteria &criteria, QString *errorMessage) {
    QString cleanPath = filePath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(filePath).toLocalFile();
    }

    QFile file(cleanPath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        if (errorMessage) *errorMessage = QStringLiteral("Could not open file for writing: %1").arg(file.errorString());
        return false;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);

    out << "\xEF\xBB\xBF";

    out << "Reference,SKU,Barcode,Name,Shape,Carat,Color,Clarity,Cut,Polish,Symmetry,Fluorescence,"
        << "Table %,Depth %,Length mm,Width mm,Height mm,Certificate Lab,Certificate Number,Certificate Date,"
        << "Purchase Cost (MAD),Selling Price (MAD),Discount Price (MAD),Status,Location,Location Details,Supplier,Archived,Created At\n";

    DiamondRepository repo;
    QList<Diamond> list = repo.getList(criteria);

    for (const auto &d : list) {
        QStringList row;
        row << escapeCsvField(d.reference());
        row << escapeCsvField(d.sku());
        row << escapeCsvField(d.barcode());
        row << escapeCsvField(d.name());
        row << escapeCsvField(d.shape());
        row << QString::number(d.caratWeight(), 'f', 2);
        row << escapeCsvField(d.color());
        row << escapeCsvField(d.clarity());
        row << escapeCsvField(d.cut());
        row << escapeCsvField(d.polish());
        row << escapeCsvField(d.symmetry());
        row << escapeCsvField(d.fluorescence());
        row << QString::number(d.tablePercentage(), 'f', 1);
        row << QString::number(d.depthPercentage(), 'f', 1);
        row << QString::number(d.lengthMm(), 'f', 2);
        row << QString::number(d.widthMm(), 'f', 2);
        row << QString::number(d.heightMm(), 'f', 2);
        row << escapeCsvField(d.certificateLab());
        row << escapeCsvField(d.certificateNumber());
        row << escapeCsvField(d.certificateDate());
        row << QString::number(d.purchasePrice().toDouble(), 'f', 2);
        row << QString::number(d.sellingPrice().toDouble(), 'f', 2);
        row << QString::number(d.discountPrice().toDouble(), 'f', 2);
        row << escapeCsvField(d.status());
        row << escapeCsvField(d.location());
        row << escapeCsvField(d.locationDetails());
        row << escapeCsvField(d.supplierName());
        row << (d.archived() ? QStringLiteral("Yes") : QStringLiteral("No"));
        row << escapeCsvField(d.createdAt());

        out << row.join(QStringLiteral(",")) << "\n";
    }

    file.close();
    return true;
}

bool ExportService::exportToPdf(const QString &filePath, const DiamondFilterCriteria &criteria, QString *errorMessage) {
    QString cleanPath = filePath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(filePath).toLocalFile();
    }

    QPdfWriter writer(cleanPath);
    writer.setPageSize(QPageSize(QPageSize::A4));
    writer.setPageOrientation(QPageLayout::Landscape);
    writer.setPageMargins(QMarginsF(15, 15, 15, 15), QPageLayout::Millimeter);

    QPainter painter(&writer);
    if (!painter.isActive()) {
        if (errorMessage) *errorMessage = QStringLiteral("Failed to initialize PDF painter for: %1").arg(cleanPath);
        return false;
    }

    DiamondRepository repo;
    QList<Diamond> list = repo.getList(criteria);

    QFont headerFont(QStringLiteral("sans-serif"), 14, QFont::Bold);
    QFont subFont(QStringLiteral("sans-serif"), 9);
    QFont colFont(QStringLiteral("sans-serif"), 8, QFont::Bold);
    QFont cellFont(QStringLiteral("sans-serif"), 7);

    int y = 200;
    painter.setFont(headerFont);
    painter.setPen(QColor(15, 23, 42));
    painter.drawText(200, y, QStringLiteral("DIAMOND INVENTORY REPORT"));

    y += 200;
    painter.setFont(subFont);
    painter.setPen(QColor(100, 116, 139));
    QString store = AppSettings::instance().storeName();
    QString dateStr = QDateTime::currentDateTime().toString(QStringLiteral("dd/MM/yyyy HH:mm"));
    painter.drawText(200, y, QStringLiteral("%1 | Generated: %2 | Total Records: %3").arg(store, dateStr, QString::number(list.size())));

    y += 350;

    int cols[] = { 200, 1100, 2600, 3300, 3900, 4500, 5200, 6200, 7400, 8600, 9600 };
    QString headers[] = {
        QStringLiteral("Ref"), QStringLiteral("Name"), QStringLiteral("Shape"),
        QStringLiteral("Carat"), QStringLiteral("Color"), QStringLiteral("Clarity"),
        QStringLiteral("Cut"), QStringLiteral("Cert #"), QStringLiteral("Purchase"),
        QStringLiteral("Selling"), QStringLiteral("Status")
    };

    painter.fillRect(180, y - 180, 9600, 240, QColor(241, 245, 249));
    painter.setFont(colFont);
    painter.setPen(QColor(30, 41, 59));
    for (int i = 0; i < 11; ++i) {
        painter.drawText(cols[i], y, headers[i]);
    }

    y += 200;
    painter.setFont(cellFont);
    painter.setPen(QColor(51, 65, 85));

    int rowIdx = 0;
    for (const auto &d : list) {
        if (y > 6800) {
            writer.newPage();
            y = 300;
            painter.fillRect(180, y - 180, 9600, 240, QColor(241, 245, 249));
            painter.setFont(colFont);
            painter.setPen(QColor(30, 41, 59));
            for (int i = 0; i < 11; ++i) {
                painter.drawText(cols[i], y, headers[i]);
            }
            y += 200;
            painter.setFont(cellFont);
            painter.setPen(QColor(51, 65, 85));
        }

        if (rowIdx % 2 == 1) {
            painter.fillRect(180, y - 140, 9600, 180, QColor(248, 250, 252));
        }

        painter.drawText(cols[0], y, d.reference());
        painter.drawText(cols[1], y, painter.fontMetrics().elidedText(d.name(), Qt::ElideRight, 1400));
        painter.drawText(cols[2], y, d.shape());
        painter.drawText(cols[3], y, QString::number(d.caratWeight(), 'f', 2) + QStringLiteral(" ct"));
        painter.drawText(cols[4], y, d.color());
        painter.drawText(cols[5], y, d.clarity());
        painter.drawText(cols[6], y, d.cut());
        painter.drawText(cols[7], y, painter.fontMetrics().elidedText(d.certificateNumber(), Qt::ElideRight, 1100));
        painter.drawText(cols[8], y, d.purchasePrice().formatted());
        painter.drawText(cols[9], y, d.sellingPrice().formatted());
        painter.drawText(cols[10], y, d.status());

        y += 180;
        rowIdx++;
    }

    painter.end();
    return true;
}
