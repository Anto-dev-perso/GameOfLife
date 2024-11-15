#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "UIParameters.hpp"
#include "UIGrid.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UIParameters>("UIBridge", 1, 0, "UIParameters");
    qmlRegisterType<UIGrid>("UIBridge", 1, 0, "UIGrid");

    const QUrl url(QStringLiteral("qrc:/QtGameOfLife/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
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
    //     { QCoreApplication::exit(-1); },
    //     Qt::QueuedConnection);

    // // engine.loadFromModule("QtGameOfLife", "Main");
    // engine.load(QUrl(QStringLiteral("qrc:/QtGameOfLife/Main.qml")));

    return app.exec();
}
