#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <iostream>

#include "src/Front/Bridge/UIParameters.hpp"
#include "src/Front/Bridge/UIGrid.hpp"

int main(int argc, char* argv[])
{
    UIGrid gridData;
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UIParameters>("UIBridge", 1, 0, "UIParameters");
     qmlRegisterType<UIGrid>("UIBridge", 1, 0, "UIGrid");

    // UIParameters uiParameters;
    // engine.rootContext()->setContextProperty("uiParameters", &uiParameters);
//    engine.rootContext()->setContextProperty("gridData", &gridData);
    // qmlRegisterSingletonType<UIGrid>("UIBridge", 1, 0, "UIGrid",
    //                                  [](QQmlEngine* engine, QJSEngine* scriptEngine) -> QObject* {
    //                                      Q_UNUSED(engine)
    //                                      Q_UNUSED(scriptEngine)
    //                                      auto* grid = new UIGrid();
    //                                      QQmlEngine::setObjectOwnership(grid, QQmlEngine::CppOwnership);
    //                                      // Let QML manage the lifecycle
    //                                      return grid;
    //                                  });

    const QUrl url{"qrc:/QtGameOfLife/src/Front/Main.qml"};
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    // QObject::connect(
    //     &engine,
    //     &QQmlApplicationEngine::objectCreationFailed,
    //     &app,
    //     []()
    //     {
    //         QCoreApplication::exit(-1);
    //     },
    //     Qt::QueuedConnection);
    //
    // // engine.loadFromModule("QtGameOfLife", "Main");
    // engine.load(QUrl(QStringLiteral("qrc:/QtGameOfLife/src/Front/Main.qml")));

    return app.exec();
}
