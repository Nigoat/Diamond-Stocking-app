#include "DateUtils.h"
#include <QLocale>

QString DateUtils::currentUtcIsoString() {
    return QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
}

QString DateUtils::formatDisplayDate(const QString &isoDateString) {
    if (isoDateString.isEmpty()) return QString();
    QDateTime dt = QDateTime::fromString(isoDateString, Qt::ISODate);
    if (!dt.isValid()) {
        QDate d = QDate::fromString(isoDateString, QStringLiteral("yyyy-MM-dd"));
        if (d.isValid()) return d.toString(QStringLiteral("dd/MM/yyyy"));
        return isoDateString;
    }
    return dt.toLocalTime().toString(QStringLiteral("dd/MM/yyyy"));
}

QString DateUtils::formatDisplayDateTime(const QString &isoDateTimeString) {
    if (isoDateTimeString.isEmpty()) return QString();
    QDateTime dt = QDateTime::fromString(isoDateTimeString, Qt::ISODate);
    if (!dt.isValid()) {
        dt = QDateTime::fromString(isoDateTimeString, QStringLiteral("yyyy-MM-dd HH:mm:ss"));
        if (!dt.isValid()) return isoDateTimeString;
    }
    return dt.toLocalTime().toString(QStringLiteral("dd/MM/yyyy HH:mm"));
}

QString DateUtils::formatTimestampForFilename(const QDateTime &dt) {
    return dt.toString(QStringLiteral("yyyy-MM-dd_HHmmss"));
}
