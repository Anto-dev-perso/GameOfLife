#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "Bridge/UIBridge.hpp"


int main(int argc, char* argv[])
{
    qputenv("QSG_RENDER_LOOP", "threaded");
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL, false);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES, true);

    const QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<UIBridge>("UIBridge", 1, 0, "UIBridge");

    const QUrl url{"qrc:/QtGameOfLife/src/Front/Main.qml"};
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](const QObject* obj, const QUrl& objUrl)
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
