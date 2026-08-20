#include <QtTest>
#include "Money.h"

class TestPricing : public QObject {
    Q_OBJECT

private slots:
    void testMoneyFromDouble() {
        Money m = Money::fromDouble(12500.50);
        QCOMPARE(m.cents(), 1250050);
        QCOMPARE(m.toDouble(), 12500.50);
    }

    void testMoneyFormatting() {
        Money m = Money::fromDouble(15000.00);
        QString str = m.formatted(QStringLiteral("MAD"));
        QVERIFY(str.contains(QStringLiteral("MAD")));
        QVERIFY(str.contains(QStringLiteral("15")));
    }

    void testMarginCalculation() {
        Money purchase = Money::fromDouble(10000.00);
        Money selling = Money::fromDouble(13000.00);
        Money margin = Money::calculateMargin(selling, purchase);
        QCOMPARE(margin.toDouble(), 3000.00);

        double pct = Money::calculateMarginPercentage(selling, purchase);
        QCOMPARE(pct, 30.0);
    }

    void testArithmetic() {
        Money a = Money::fromDouble(100.25);
        Money b = Money::fromDouble(50.75);
        Money sum = a + b;
        QCOMPARE(sum.toDouble(), 151.00);

        Money diff = a - b;
        QCOMPARE(diff.toDouble(), 49.50);

        Money mult = a * 1.10;
        QCOMPARE(mult.toDouble(), 110.28);
    }
};

QTEST_MAIN(TestPricing)
#include "tst_pricing.moc"
