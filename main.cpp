#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "drawingboard.h"

QStringList vectorModel;
QQmlApplicationEngine *g_engine;

void notifyModel() {
    g_engine->rootContext()->setContextProperty("vectorModel", QVariant::fromValue(vectorModel));
}

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    g_engine = &engine;

    qmlRegisterType<DrawingBoard>("luyiming", 1, 0, "DrawingBoard");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    engine.rootContext()->setContextProperty("vectorModel", QVariant::fromValue(vectorModel));

    return app.exec();
}
