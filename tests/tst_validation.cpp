#include <QtTest>
#include <QGuiApplication>
#include "InventoryService.h"
#include "DatabaseManager.h"
#include <QTemporaryDir>

class TestValidation : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        m_tempDir = std::make_unique<QTemporaryDir>();
        QVERIFY(m_tempDir->isValid());
        QString dbPath = m_tempDir->path() + "/val_inventory.db";
        QVERIFY(DatabaseManager::instance().initialize(dbPath));
    }

    void testEmptyReference() {
        Diamond d;
        d.setReference(QStringLiteral(""));
        d.setName(QStringLiteral("Valid Name"));

        QString err;
        QVERIFY(!InventoryService::instance().addDiamond(d, &err));
        QVERIFY(err.contains(QStringLiteral("Reference is required")));
    }

    void testEmptyName() {
        Diamond d;
        d.setReference(QStringLiteral("REF-VAL-001"));
        d.setName(QStringLiteral(""));

        QString err;
        QVERIFY(!InventoryService::instance().addDiamond(d, &err));
        QVERIFY(err.contains(QStringLiteral("Name is required")));
    }

    void testNegativeCarat() {
        Diamond d;
        d.setReference(QStringLiteral("REF-VAL-002"));
        d.setName(QStringLiteral("Invalid Carat"));
        d.setCartWeight(-1.5);

        QString err;
        QVERIFY(!InventoryService::instance().addDiamond(d, &err));
        QVERIFY(err.contains(QStringLiteral("Carat weight cannot be negative")));
    }

    void testNegativePrice() {
        Diamond d;
        d.setReference(QStringLiteral("REF-VAL-003"));
        d.setName(QStringLiteral("Invalid Price"));
        d.setPurchasePriceCents(-500);

        QString err;
        QVERIFY(!InventoryService::instance().addDiamond(d, &err));
        QVERIFY(err.contains(QStringLiteral("Price cannot be negative")));
    }

    void testDuplicateDiamond() {
        Diamond d;
        d.setReference(QStringLiteral("REF-VAL-004"));
        d.setName(QStringLiteral("Original Solitaire"));
        d.setCartWeight(1.20);
        d.setSellingPriceCents(1500000);

        QString err;
        QVERIFY(InventoryService::instance().addDiamond(d, &err));
        QVERIFY(d.id() > 0);

        auto copyOpt = InventoryService::instance().duplicateDiamond(d.id(), &err);
        QVERIFY(copyOpt.has_value());
        QCOMPARE(copyOpt.value().caratWeight(), 1.20);
        QCOMPARE(copyOpt.value().sellingPriceCents(), 1500000);
        QVERIFY(copyOpt.value().reference() != d.reference());
    }

    void cleanupTestCase() {
        DatabaseManager::instance().close();
    }

private:
    std::unique_ptr<QTemporaryDir> m_tempDir;
};

int main(int argc, char *argv[]) {
    qputenv("QT_QPA_PLATFORM", "offscreen");
    QGuiApplication app(argc, argv);
    TestValidation tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "tst_validation.moc"
