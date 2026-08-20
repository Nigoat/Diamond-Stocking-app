#ifndef MONEY_H
#define MONEY_H

#include <QString>
#include <QtGlobal>
#include <cmath>

class Money {
public:
    constexpr Money() : m_cents(0) {}
    constexpr explicit Money(qint64 cents) : m_cents(cents) {}

    static Money fromDouble(double amount) {
        return Money(static_cast<qint64>(std::round(amount * 100.0)));
    }

    static Money fromCents(qint64 cents) {
        return Money(cents);
    }

    qint64 cents() const { return m_cents; }
    double toDouble() const { return static_cast<double>(m_cents) / 100.0; }

    QString formatted(const QString &currency = QStringLiteral("MAD")) const;
    QString rawNumberString() const;

    Money operator+(const Money &other) const { return Money(m_cents + other.m_cents); }
    Money operator-(const Money &other) const { return Money(m_cents - other.m_cents); }
    Money operator*(double factor) const {
        return Money(static_cast<qint64>(std::round(static_cast<double>(m_cents) * factor)));
    }
    Money operator/(double divisor) const {
        if (std::abs(divisor) < 1e-9) return Money(0);
        return Money(static_cast<qint64>(std::round(static_cast<double>(m_cents) / divisor)));
    }

    bool operator==(const Money &other) const { return m_cents == other.m_cents; }
    bool operator!=(const Money &other) const { return m_cents != other.m_cents; }
    bool operator<(const Money &other) const { return m_cents < other.m_cents; }
    bool operator<=(const Money &other) const { return m_cents <= other.m_cents; }
    bool operator>(const Money &other) const { return m_cents > other.m_cents; }
    bool operator>=(const Money &other) const { return m_cents >= other.m_cents; }

    static Money calculateMargin(const Money &selling, const Money &purchase) {
        return selling - purchase;
    }

    static double calculateMarginPercentage(const Money &selling, const Money &purchase) {
        if (purchase.cents() <= 0) return 0.0;
        return (static_cast<double>(selling.cents() - purchase.cents()) / static_cast<double>(purchase.cents())) * 100.0;
    }

private:
    qint64 m_cents;
};

#endif
