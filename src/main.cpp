#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>
#include <QMessageBox>
#include <QStandardPaths>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include "AppPaths.h"
#include "DatabaseManager.h"
#include "ApplicationController.h"
#include "AppSettings.h"

static QFile g_logFile;

static void qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (!g_logFile.isOpen()) {
        // best-effort: try to open log
        QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
        QDir().mkpath(logPath);
        g_logFile.setFileName(logPath + QDir::separator() + "startup-log.txt");
        g_logFile.open(QIODevice::Append | QIODevice::Text);
    }
    if (g_logFile.isOpen()) {
        QTextStream ts(&g_logFile);
        ts << QDateTime::currentDateTime().toString(Qt::ISODate) << " ";
        switch (type) {
            case QtDebugMsg: ts << "DEBUG: "; break;
            case QtInfoMsg: ts << "INFO: "; break;
            case QtWarningMsg: ts << "WARN: "; break;
            case QtCriticalMsg: ts << "CRIT: "; break;
            case QtFatalMsg: ts << "FATAL: "; break;
        }
        ts << msg << " (" << context.file << ":" << context.line << ")\n";
        ts.flush();
    }
    if (type == QtFatalMsg) {
        abort();
    }
}

int main(int argc, char *argv[]) {
    // Mark process start as early as possible
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir().mkpath(dataPath);
    QFile marker(dataPath + QDir::separator() + "startup-marker.txt");
    if (marker.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream t(&marker);
        t << "started at " << QDateTime::currentDateTime().toString(Qt::ISODate) << "\n";
        marker.close();
    }

    // install Qt message handler to capture Qt logging to file
    qInstallMessageHandler(qtMessageHandler);

    QGuiApplication::setOrganizationName(QStringLiteral("DiamondStore"));
    QGuiApplication::setOrganizationDomain(QStringLiteral("diamondstore.local"));
    QGuiApplication::setApplicationName(QStringLiteral("Diamond Inventory"));
    QGuiApplication::setApplicationVersion(QStringLiteral("1.0.0"));

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/resources/icons/app_icon.svg")));

    QQuickStyle::setStyle(QStringLiteral("Basic"));

    // Log that we're past construction
    qInfo() << "QGuiApplication constructed";

    AppPaths::instance().initialize();
    qInfo() << "AppPaths initialized";
    DatabaseManager::instance().initialize();
    qInfo() << "DatabaseManager initialized";

    QQmlApplicationEngine engine;

    ApplicationController controller;
    controller.initialize();
    qInfo() << "ApplicationController initialized";

    engine.rootContext()->setContextProperty(QStringLiteral("AppController"), &controller);
    engine.rootContext()->setContextProperty(QStringLiteral("DiamondModel"), controller.diamondModel());
    engine.rootContext()->setContextProperty(QStringLiteral("SupplierModel"), controller.supplierModel());
    engine.rootContext()->setContextProperty(QStringLiteral("Settings"), controller.settings());

    const QUrl url(QStringLiteral("qrc:/DiamondInventory/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [&engine, url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) {
            // Ensure log directory exists
            QString logPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
            QDir().mkpath(logPath);
            QFile f(logPath + QDir::separator() + "startup-log.txt");
            if (f.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream ts(&f);
                ts << QDateTime::currentDateTime().toString(Qt::ISODate) << " QML load failed. Engine errors:\n";
                const auto errs = engine.errors();
                for (const QQmlError &e : errs) {
                    ts << e.toString() << "\n";
                }
                f.close();
            }
            QString msg = QObject::tr("The application failed to start. A startup log has been written to:\n%1")
                          .arg(QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation));
            QMessageBox::critical(nullptr, QObject::tr("Startup Error"), msg);
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);

    qInfo() << "About to load QML URL:" << url.toString();
    engine.load(url);

    qInfo() << "Entering event loop";
    return app.exec();
}
