#include "Money.h"
#include <QLocale>

QString Money::formatted(const QString &currency) const {
    QLocale locale(QLocale::French, QLocale::Morocco);
    double val = toDouble();
    QString formattedVal = locale.toString(val, 'f', 2);
    if (currency.isEmpty()) {
        return formattedVal;
    }
    return QStringLiteral("%1 %2").arg(formattedVal, currency);
}

QString Money::rawNumberString() const {
    return QString::number(toDouble(), 'f', 2);
}
