#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>

class DrawingBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    DrawingBoard(QQuickItem *parent = 0);
    void paint(QPainter *painter);

public:
    Q_INVOKABLE void handleMousePress(int x, int y, int button, int buttons, int modifiers) {
        QMouseEvent event(QEvent::MouseButtonPress, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
        update();
//        qDebug() <<"new mouse pressed" << event.pos() << event.buttons();
    }

    Q_INVOKABLE void handleMouseRelease(int x, int y, int button, int buttons, int modifiers) {
        QMouseEvent event(QEvent::MouseButtonRelease, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
//        qDebug() <<"new mouse release" << event.pos() << event.buttons();
    }

    Q_INVOKABLE void handleMouseMove(int x, int y, int button, int buttons, int modifiers) {
        QMouseEvent event(QEvent::MouseMove, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
//        qDebug() <<"new mouse move" << event.pos() << event.buttons();
    }

private:
    QImage *m_image = nullptr;
};

#endif // DRAWINGBOARD_H
