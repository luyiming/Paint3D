#include "drawingboard.h"

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>

DrawingBoard::DrawingBoard(QQuickItem *parent) : QQuickPaintedItem(parent)
{
}

void DrawingBoard::paint(QPainter *painter){
    QBrush brush(QColor("#007430"));

    painter->setBrush(brush);
    painter->setPen(QPen(QColor("#007430")));
    painter->setRenderHint(QPainter::Antialiasing);

//    painter->drawRoundedRect(0, 0, boundingRect().width(), boundingRect().height() - 10, 10, 10);

    painter->drawLine(0, 0, x, y);
    qDebug() <<"paint";
}
