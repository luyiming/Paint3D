#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>

class DrawingBoard : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int x1 READ getX WRITE setX NOTIFY sourceChanged)
    Q_PROPERTY(int y1 READ getY WRITE setY NOTIFY sourceChanged)

public:
    DrawingBoard(QQuickItem *parent = 0);

    int getX() const {return x;}
    void setX(int x) {this->x=x; qDebug()<<"setX: "<<x;}

    int getY() const {return y;}
    void setY(int y) {this->y=y;}

    void paint(QPainter *painter);

signals:
    void sourceChanged(int x);

public:

    void onSourceChanged(int x) {
        qDebug()<<"source change: "<<x;
    }

private:
    int x = 10;
    int y = 10;
};

#endif // DRAWINGBOARD_H
