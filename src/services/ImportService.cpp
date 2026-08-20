#include "ImportService.h"
#include "DiamondRepository.h"
#include "DatabaseManager.h"
#include "Money.h"
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QVariantList>

QVariantMap ImportPreviewResult::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("success")] = success;
    map[QStringLiteral("errorMessage")] = errorMessage;
    map[QStringLiteral("headers")] = headers;
    QVariantList rowsList;
    for (const auto &row : previewRows) {
        rowsList.append(QVariant::fromValue(row));
    }
    map[QStringLiteral("previewRows")] = rowsList;
    map[QStringLiteral("totalRows")] = totalRows;
    return map;
}

QVariantMap ImportExecutionResult::toVariantMap() const {
    QVariantMap map;
    map[QStringLiteral("success")] = success;
    map[QStringLiteral("totalRows")] = totalRows;
    map[QStringLiteral("importedCount")] = importedCount;
    map[QStringLiteral("warningCount")] = warningCount;
    map[QStringLiteral("errorCount")] = errorCount;
    map[QStringLiteral("errors")] = errors;
    map[QStringLiteral("warnings")] = warnings;
    return map;
}

ImportService &ImportService::instance() {
    static ImportService inst;
    return inst;
}

static QStringList parseCsvLine(const QString &line) {
    QStringList fields;
    QString curField;
    bool inQuotes = false;

    for (int i = 0; i < line.length(); ++i) {
        QChar c = line.at(i);
        if (c == QLatin1Char('"')) {
            if (inQuotes && i + 1 < line.length() && line.at(i + 1) == QLatin1Char('"')) {
                curField.append(QLatin1Char('"'));
                i++;
            } else {
                inQuotes = !inQuotes;
            }
        } else if (c == QLatin1Char(',') && !inQuotes) {
            fields.append(curField.trimmed());
            curField.clear();
        } else {
            curField.append(c);
        }
    }
    fields.append(curField.trimmed());
    return fields;
}

QList<QStringList> ImportService::parseCsvFile(const QString &filePath, QString *errorMessage) {
    QList<QStringList> records;
    QString cleanPath = filePath;
    if (cleanPath.startsWith(QStringLiteral("file://"))) {
        cleanPath = QUrl(filePath).toLocalFile();
    }

    QFile file(cleanPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        if (errorMessage) *errorMessage = QStringLiteral("Cannot open CSV file: %1").arg(file.errorString());
        return records;
    }

    QTextStream in(&file);
    in.setEncoding(QStringConverter::Utf8);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;
        if (records.isEmpty() && line.startsWith(QChar(0xFEFF))) {
            line = line.mid(1);
        }
        records.append(parseCsvLine(line));
    }
    file.close();
    return records;
}

ImportPreviewResult ImportService::previewCsv(const QString &filePath) {
    ImportPreviewResult res;
    QString error;
    QList<QStringList> allRows = parseCsvFile(filePath, &error);

    if (allRows.isEmpty()) {
        res.success = false;
        res.errorMessage = error.isEmpty() ? QStringLiteral("CSV file is empty.") : error;
        return res;
    }

    res.headers = allRows.first();
    res.totalRows = allRows.size() - 1;

    for (int i = 1; i < std::min(static_cast<int>(allRows.size()), 6); ++i) {
        res.previewRows.append(allRows[i]);
    }

    res.success = true;
    return res;
}

ImportExecutionResult ImportService::executeImport(const QString &filePath, const QVariantMap &columnMap) {
    ImportExecutionResult res;
    QString parseErr;
    QList<QStringList> allRows = parseCsvFile(filePath, &parseErr);

    if (allRows.size() < 2) {
        res.success = false;
        res.errors.append(parseErr.isEmpty() ? QStringLiteral("No data rows found in CSV.") : parseErr);
        return res;
    }

    QStringList headers = allRows.first();
    res.totalRows = allRows.size() - 1;

    auto getColIndex = [&](const QString &fieldKey) -> int {
        if (columnMap.contains(fieldKey)) {
            QString mappedHeader = columnMap.value(fieldKey).toString();
            int idx = headers.indexOf(mappedHeader);
            if (idx >= 0) return idx;
        }
        for (int i = 0; i < headers.size(); ++i) {
            QString h = headers[i].toLower().remove(QLatin1Char('_')).remove(QLatin1Char(' '));
            QString k = fieldKey.toLower().remove(QLatin1Char('_')).remove(QLatin1Char(' '));
            if (h.contains(k) || k.contains(h)) {
                return i;
            }
        }
        return -1;
    };

    int refIdx = getColIndex(QStringLiteral("reference"));
    int nameIdx = getColIndex(QStringLiteral("name"));
    int caratIdx = getColIndex(QStringLiteral("carat"));
    int shapeIdx = getColIndex(QStringLiteral("shape"));
    int colorIdx = getColIndex(QStringLiteral("color"));
    int clarityIdx = getColIndex(QStringLiteral("clarity"));
    int cutIdx = getColIndex(QStringLiteral("cut"));
    int certLabIdx = getColIndex(QStringLiteral("certificatelab"));
    int certNumIdx = getColIndex(QStringLiteral("certificatenumber"));
    int purchaseIdx = getColIndex(QStringLiteral("purchasecost"));
    int sellingIdx = getColIndex(QStringLiteral("sellingprice"));
    int statusIdx = getColIndex(QStringLiteral("status"));
    int locIdx = getColIndex(QStringLiteral("location"));
    int skuIdx = getColIndex(QStringLiteral("sku"));
    int barcodeIdx = getColIndex(QStringLiteral("barcode"));

    if (refIdx < 0) {
        res.success = false;
        res.errors.append(QStringLiteral("Reference column could not be identified or mapped."));
        return res;
    }

    DiamondRepository repo;
    DatabaseManager::instance().beginTransaction();

    for (int r = 1; r < allRows.size(); ++r) {
        const QStringList &row = allRows[r];
        if (row.isEmpty()) continue;

        auto getVal = [&](int idx) -> QString {
            if (idx >= 0 && idx < row.size()) return row[idx].trimmed();
            return QString();
        };

        QString ref = getVal(refIdx);
        if (ref.isEmpty()) {
            res.errorCount++;
            res.errors.append(QStringLiteral("Row %1: Reference is empty.").arg(r));
            continue;
        }

        if (repo.referenceExists(ref)) {
            res.errorCount++;
            res.errors.append(QStringLiteral("Row %1: Reference '%2' already exists in inventory.").arg(QString::number(r), ref));
            continue;
        }

        Diamond d;
        d.setReference(ref);
        d.setName(nameIdx >= 0 ? getVal(nameIdx) : QStringLiteral("Diamond %1").arg(ref));
        if (d.name().isEmpty()) d.setName(QStringLiteral("Diamond %1").arg(ref));

        d.setCartWeight(caratIdx >= 0 ? getVal(caratIdx).toDouble() : 1.0);
        d.setShape(shapeIdx >= 0 && !getVal(shapeIdx).isEmpty() ? getVal(shapeIdx) : QStringLiteral("Round"));
        d.setColor(colorIdx >= 0 && !getVal(colorIdx).isEmpty() ? getVal(colorIdx) : QStringLiteral("G"));
        d.setClarity(clarityIdx >= 0 && !getVal(clarityIdx).isEmpty() ? getVal(clarityIdx) : QStringLiteral("VS1"));
        d.setCut(cutIdx >= 0 && !getVal(cutIdx).isEmpty() ? getVal(cutIdx) : QStringLiteral("Excellent"));
        d.setCertificateLab(certLabIdx >= 0 && !getVal(certLabIdx).isEmpty() ? getVal(certLabIdx) : QStringLiteral("None"));
        d.setCertificateNumber(certNumIdx >= 0 ? getVal(certNumIdx) : QString());

        double pCost = purchaseIdx >= 0 ? getVal(purchaseIdx).toDouble() : 0.0;
        double sPrice = sellingIdx >= 0 ? getVal(sellingIdx).toDouble() : 0.0;
        d.setPurchasePriceCents(Money::fromDouble(pCost).cents());
        d.setSellingPriceCents(Money::fromDouble(sPrice).cents());

        d.setStatus(statusIdx >= 0 && !getVal(statusIdx).isEmpty() ? getVal(statusIdx) : QStringLiteral("Available"));
        d.setLocation(locIdx >= 0 && !getVal(locIdx).isEmpty() ? getVal(locIdx) : QStringLiteral("Store"));
        d.setSku(skuIdx >= 0 ? getVal(skuIdx) : QString());
        d.setBarcode(barcodeIdx >= 0 ? getVal(barcodeIdx) : QString());

        QString insertErr;
        if (!repo.insert(d, &insertErr)) {
            res.errorCount++;
            res.errors.append(QStringLiteral("Row %1 (%2): %3").arg(QString::number(r), ref, insertErr));
        } else {
            res.importedCount++;
        }
    }

    DatabaseManager::instance().commitTransaction();
    res.success = (res.importedCount > 0);
    return res;
}
