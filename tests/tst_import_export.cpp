#include <QtTest>
#include <QGuiApplication>
#include "ImportService.h"
#include "ExportService.h"
#include "DatabaseManager.h"
#include "DiamondRepository.h"
#include <QTemporaryDir>
#include <QFile>
#include <QTextStream>

class TestImportExport : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        m_tempDir = std::make_unique<QTemporaryDir>();
        QVERIFY(m_tempDir->isValid());
        QString dbPath = m_tempDir->path() + "/io_inventory.db";
        QVERIFY(DatabaseManager::instance().initialize(dbPath));
    }

    void testExportAndImportCycle() {
        DiamondRepository repo;
        Diamond d1;
        d1.setReference(QStringLiteral("EXP-001"));
        d1.setName(QStringLiteral("Export Diamond One"));
        d1.setCartWeight(1.00);
        d1.setShape(QStringLiteral("Round"));
        d1.setColor(QStringLiteral("D"));
        d1.setClarity(QStringLiteral("VVS1"));
        d1.setPurchasePriceCents(3000000);
        d1.setSellingPriceCents(4500000);
        repo.insert(d1);

        Diamond d2;
        d2.setReference(QStringLiteral("EXP-002"));
        d2.setName(QStringLiteral("Export Diamond Two"));
        d2.setCartWeight(2.00);
        d2.setShape(QStringLiteral("Oval"));
        d2.setColor(QStringLiteral("F"));
        d2.setClarity(QStringLiteral("VS1"));
        d2.setPurchasePriceCents(8000000);
        d2.setSellingPriceCents(11000000);
        repo.insert(d2);

        QString csvPath = m_tempDir->path() + "/exported.csv";
        DiamondFilterCriteria criteria;
        QString err;
        QVERIFY(ExportService::instance().exportToCsv(csvPath, criteria, &err));
        QVERIFY(QFile::exists(csvPath));

        auto preview = ImportService::instance().previewCsv(csvPath);
        QVERIFY(preview.success);
        QCOMPARE(preview.totalRows, 2);

        QString customCsv = m_tempDir->path() + "/new_import.csv";
        QFile file(customCsv);
        QVERIFY(file.open(QIODevice::WriteOnly | QIODevice::Text));
        QTextStream out(&file);
        out << "reference,name,carat,shape,color,clarity,purchasecost,sellingprice,status\n";
        out << "IMP-101,Imported Solitaire,1.25,Round,G,VS2,4000,5500,Available\n";
        out << "IMP-102,Imported Cushion,1.75,Cushion,E,VVS2,7000,9500,Available\n";
        file.close();

        auto result = ImportService::instance().executeImport(customCsv, {});
        QVERIFY(result.success);
        QCOMPARE(result.importedCount, 2);
        QCOMPARE(result.errorCount, 0);

        auto importedD = repo.getByReference(QStringLiteral("IMP-101"));
        QVERIFY(importedD.has_value());
        QCOMPARE(importedD.value().caratWeight(), 1.25);
        QCOMPARE(importedD.value().shape(), QStringLiteral("Round"));
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
    TestImportExport tc;
    return QTest::qExec(&tc, argc, argv);
}
#include "tst_import_export.moc"
