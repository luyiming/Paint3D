#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "drawingboard.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<DrawingBoard>("luyiming", 1, 0, "DrawingBoard");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
