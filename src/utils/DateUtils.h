#ifndef DATEUTILS_H
#define DATEUTILS_H

#include <QString>
#include <QDateTime>

class DateUtils {
public:
    static QString currentUtcIsoString();
    static QString formatDisplayDate(const QString &isoDateString);
    static QString formatDisplayDateTime(const QString &isoDateTimeString);
    static QString formatTimestampForFilename(const QDateTime &dt = QDateTime::currentDateTimeUtc());
};

#endif
