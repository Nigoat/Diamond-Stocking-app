#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QIcon>
#include <QQuickStyle>
#include "AppPaths.h"
#include "DatabaseManager.h"
#include "ApplicationController.h"
#include "AppSettings.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setOrganizationName(QStringLiteral("DiamondStore"));
    QGuiApplication::setOrganizationDomain(QStringLiteral("diamondstore.local"));
    QGuiApplication::setApplicationName(QStringLiteral("Diamond Inventory"));
    QGuiApplication::setApplicationVersion(QStringLiteral("1.0.0"));

    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/resources/icons/app_icon.svg")));

    QQuickStyle::setStyle(QStringLiteral("Basic"));

    AppPaths::instance().initialize();
    DatabaseManager::instance().initialize();

    QQmlApplicationEngine engine;

    ApplicationController controller;
    controller.initialize();

    engine.rootContext()->setContextProperty(QStringLiteral("AppController"), &controller);
    engine.rootContext()->setContextProperty(QStringLiteral("DiamondModel"), controller.diamondModel());
    engine.rootContext()->setContextProperty(QStringLiteral("SupplierModel"), controller.supplierModel());
    engine.rootContext()->setContextProperty(QStringLiteral("Settings"), controller.settings());

    const QUrl url(QStringLiteral("qrc:/DiamondInventory/qml/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
