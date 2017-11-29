#include "painter.h"
#include <QImage>

namespace CorePainter {

Painter::Painter(QImage *image, QObject *parent) : QObject(parent)
{
    mImage = image;
}

void Painter::drawPixel(int x, int y, const QColor & color)
{
    mImage->setPixel(x, y, color.rgba());
}

void Painter::drawLine(const QPoint & p1, const QPoint & p2, QColor color, int width) {
    drawLineBresenham(p1.x(), p1.y(), p2.x(), p2.y(), color);
}

void Painter::drawPoint(const QPoint & position, int width) {

}

void Painter::drawLineDDA(int x1, int y1, int x2, int y2, QColor color) {
    if (x1 == x2) {
        if (y1 > y2)
            swap(y1, y2);
        for (; y1 <= y2; y1++)
            drawPixel(x1, y1, color);
        return;
    }

    double m = (double)(y2 - y1) / (x2 - x1);

    if (-1 < m && m < 1) {
        if (x1 > x2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        double x = x1, y = y1, dx = 1.0;
        while (x <= x2) {
            drawPixel((int)x, (int)floor(y + 0.5), color);
            x += dx;
            y += m;
        }
    }
    else {
        if (y1 > y2) {
            swap(x1, x2);
            swap(y1, y2);
        }
        double x = x1, y = y1, dy = 1.0;
        while (y <= y2) {
            drawPixel((int)floor(x + 0.5), (int)y, color);
            y += dy;
            x += 1 / m;
        }
    }
}

void Painter::drawLineBresenham(int x1, int y1, int x2, int y2, QColor color) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;

    while (drawPixel(x1, y1, color), x1 != x2 || y1 != y2) {
        int e2 = err;
        if (e2 > -dx) { err -= dy; x1 += sx; }
        if (e2 <  dy) { err += dx; y1 += sy; }
    }
}

void Painter::drawCircleBresenham(int x1, int y1, int r, QColor color) {
    int p = 5 - 4 * r;
    int x = 0, y = r;
    while (x <= y) {
        drawPixel(x1 + x, y1 + y, color);
        drawPixel(x1 + x, y1 - y, color);
        drawPixel(x1 - x, y1 - y, color);
        drawPixel(x1 - x, y1 + y, color);
        drawPixel(x1 + y, y1 + x, color);
        drawPixel(x1 + y, y1 - x, color);
        drawPixel(x1 - y, y1 - x, color);
        drawPixel(x1 - y, y1 + x, color);

        if (p < 0) {
            p = p + 8 * x + 12;
        }
        else {
            p = p + 8 * (x + 1) + 12 - 8 * y - 8;
            y--;
        }
        x++;
    }
}

void Painter::drawEllipse(int x1, int y1, int rx, int ry, QColor color) {
    if (rx == ry) {
        drawCircleBresenham(x1, y1, rx, color);
        return;
    }

    bool xy_flip = false;
    if (ry > rx) {
        swap(rx, ry);
        xy_flip = true;
    }

    int x = 0, y = ry;
    int rx2 = rx * rx, ry2 = ry * ry;
    int p = 4 * ry * ry - 4 * rx2 * ry + rx2;

    // area 1
    while (ry2 * x < rx2 * y) {
        if (xy_flip) {
            drawPixel(x1 + y, y1 + x, color);
            drawPixel(x1 + y, y1 - x, color);
            drawPixel(x1 - y, y1 - x, color);
            drawPixel(x1 - y, y1 + x, color);
        }
        else {
            drawPixel(x1 + x, y1 + y, color);
            drawPixel(x1 + x, y1 - y, color);
            drawPixel(x1 - x, y1 - y, color);
            drawPixel(x1 - x, y1 + y, color);
        }

        if (p < 0) {
            p = p + ry2 * (8 * x + 12);
        }
        else {
            p = p + ry2 * (8 * x + 12) - rx2 * (8 * y - 8);
            y--;
        }
        x++;
    }

    // area 2
    p = ry2 * (2 * x + 1) * (2 * x + 1) + 4 * rx2 * (y - 1) * (y - 1) - 4 * rx2 * ry2;
    while (y >= 0) {
        if (xy_flip) {
            drawPixel(x1 + y, y1 + x, color);
            drawPixel(x1 + y, y1 - x, color);
            drawPixel(x1 - y, y1 - x, color);
            drawPixel(x1 - y, y1 + x, color);
        }
        else {
            drawPixel(x1 + x, y1 + y, color);
            drawPixel(x1 + x, y1 - y, color);
            drawPixel(x1 - x, y1 - y, color);
            drawPixel(x1 - x, y1 + y, color);
        }

        if (p > 0) {
            p = p - rx * rx * (8 * y - 12);
        }
        else {
            p = p + ry * ry * (8 * x + 8) - rx * rx * (8 * y - 12);
            x++;
        }
        y--;
    }
}

}
