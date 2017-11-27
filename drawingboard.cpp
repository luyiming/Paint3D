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
    if (m_image == nullptr) {
        m_image = new QImage(width(), height(), QImage::Format_RGB32);
        QPainter *painter = new QPainter(m_image);
        painter->fillRect(0, 0, m_image->width(), m_image->height(), Qt::white);
        painter->end();
    }

    painter->drawImage(QPoint(0, 0), *m_image);

    qDebug() <<"paint";
}
