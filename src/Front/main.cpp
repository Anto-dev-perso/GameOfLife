#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Bridge/UIBridge.hpp"
#include "Bridge/MainGridImageProvider.hpp"

int main(int argc, char* argv[])
{
    int returnVal{1};
    const QGuiApplication app(argc, argv);
    UIBridge uiBridge;
    {
        QQmlApplicationEngine engine;

        uiBridge.initialize(&engine);
        engine.rootContext()->setContextProperty("uiBridge", &uiBridge);

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

        returnVal = app.exec();
    }

    return returnVal;
}
