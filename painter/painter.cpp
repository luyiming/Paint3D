#include "painter.h"

Painter::Painter(QImage *image, QObject *parent) : QObject(parent)
{
    m_image = image;
}

void Painter::setPixel(int x, int y, const QColor & color)
{
    m_image->setPixel(x, y, color.rgb());
}

void  Painter::drawLine(const QPoint & p1, const QPoint & p2) {

}

void  Painter::drawPoint(const QPoint & position) {

}
