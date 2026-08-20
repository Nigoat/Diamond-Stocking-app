#include <QtTest>
#include <QGuiApplication>
#include "DatabaseManager.h"
#include "DiamondRepository.h"
#include "SupplierRepository.h"
#include "FileUtils.h"
#include <QTemporaryDir>

class TestDatabase : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        m_tempDir = std::make_unique<QTemporaryDir>();
        QVERIFY(m_tempDir->isValid());
        QString dbPath = m_tempDir->path() + "/test_inventory.db";
        QVERIFY(DatabaseManager::instance().initialize(dbPath));
        QVERIFY(DatabaseManager::instance().isOpen());
    }

    void testInsertAndRetrieveDiamond() {
        DiamondRepository repo;
        Diamond d;
        d.setReference(QStringLiteral("TEST-DMD-001"));
        d.setName(QStringLiteral("Test Solitaire"));
        d.setCartWeight(1.50);
        d.setColor(QStringLiteral("E"));
        d.setClarity(QStringLiteral("VVS1"));
        d.setCut(QStringLiteral("Excellent"));
        d.setPurchasePriceCents(5000000);
        d.setSellingPriceCents(7500000);
        d.setStatus(QStringLiteral("Available"));

        QString err;
        QVERIFY(repo.insert(d, &err));
        QVERIFY(d.id() > 0);

        auto fetched = repo.getById(d.id());
        QVERIFY(fetched.has_value());
        QCOMPARE(fetched.value().reference(), QStringLiteral("TEST-DMD-001"));
        QCOMPARE(fetched.value().name(), QStringLiteral("Test Solitaire"));
        QCOMPARE(fetched.value().caratWeight(), 1.50);
        QCOMPARE(fetched.value().purchasePriceCents(), 5000000);
        QCOMPARE(fetched.value().sellingPriceCents(), 7500000);
    }

    void testDuplicateReferencePrevention() {
        DiamondRepository repo;
        Diamond d;
        d.setReference(QStringLiteral("TEST-DMD-001"));
        d.setName(QStringLiteral("Duplicate Test"));
        d.setCartWeight(1.0);

        QString err;
        QVERIFY(!repo.insert(d, &err));
        QVERIFY(repo.referenceExists(QStringLiteral("TEST-DMD-001")));
    }

    void testUpdateDiamond() {
        DiamondRepository repo;
        auto opt = repo.getByReference(QStringLiteral("TEST-DMD-001"));
        QVERIFY(opt.has_value());

        Diamond d = opt.value();
        d.setSellingPriceCents(8000000);
        d.setStatus(QStringLiteral("Reserved"));

        QString err;
        QVERIFY(repo.update(d, &err));

        auto updated = repo.getById(d.id());
        QVERIFY(updated.has_value());
        QCOMPARE(updated.value().sellingPriceCents(), 8000000);
        QCOMPARE(updated.value().status(), QStringLiteral("Reserved"));
    }

    void testArchiveDiamond() {
        DiamondRepository repo;
        auto opt = repo.getByReference(QStringLiteral("TEST-DMD-001"));
        QVERIFY(opt.has_value());

        QVERIFY(repo.setArchived(opt.value().id(), true));

        DiamondFilterCriteria activeOnly;
        activeOnly.includeArchived = false;
        QList<Diamond> activeList = repo.getList(activeOnly);
        bool foundInActive = false;
        for (const auto &item : activeList) {
            if (item.reference() == QStringLiteral("TEST-DMD-001")) foundInActive = true;
        }
        QVERIFY(!foundInActive);

        DiamondFilterCriteria allCriteria;
        allCriteria.includeArchived = true;
        QList<Diamond> allList = repo.getList(allCriteria);
        bool foundInAll = false;
        for (const auto &item : allList) {
            if (item.reference() == QStringLiteral("TEST-DMD-001")) foundInAll = true;
        }
        QVERIFY(foundInAll);
    }

    void testSupplierCrud() {
        SupplierRepository repo;
        Supplier s;
        s.setName(QStringLiteral("Atlas Diamonds"));
        s.setCompany(QStringLiteral("Atlas Gems Inc"));
        s.setPhone(QStringLiteral("+212 522 000000"));
        s.setEmail(QStringLiteral("info@atlasgems.ma"));

        QString err;
        QVERIFY(repo.insert(s, &err));
        QVERIFY(s.id() > 0);

        auto opt = repo.getById(s.id());
        QVERIFY(opt.has_value());
        QCOMPARE(opt.value().name(), QStringLiteral("Atlas Diamonds"));

        s.setName(QStringLiteral("Atlas Diamonds SARL"));
        QVERIFY(repo.update(s, &err));

        auto updated = repo.getById(s.id());
        QVERIFY(updated.has_value());
        QCOMPARE(updated.value().name(), QStringLiteral("Atlas Diamonds SARL"));

        QVERIFY(repo.remove(s.id(), &err));
        auto deleted = repo.getById(s.id());
        QVERIFY(!deleted.has_value());
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
    TestDatabase tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "tst_database.moc"
