#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "drawingboard.h"

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<DrawingBoard>("luyiming", 1, 0, "DrawingBoard");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

//    engine.rootContext()->setContextProperty("vectorModel", QVariant::fromValue(dataList));

    return app.exec();
}
