#include "painter.h"
#include <QImage>

namespace CorePainter {

Painter::Painter(QImage *image, QObject *parent) : QObject(parent)
{
    mImage = image;
}

void Painter::drawPixel(int x, int y, const QColor & color)
{
    if(x >= 0 && y >= 0 && x < mImage->width() && y < mImage->height())
        mImage->setPixel(x, y, color.rgb());
}

void Painter::drawLine(const QPoint & p1, const QPoint & p2, QColor color, int width, bool useBresenham)
{
    if (useBresenham)
        drawLineBresenham(p1.x(), p1.y(), p2.x(), p2.y(), color);
    else
        lineSDFAABB(p1.x(), p1.y(), p2.x(), p2.y(), width, color);
}

void Painter::drawPoint(const QPoint & position, int width)
{
    Q_UNUSED(position);
    Q_UNUSED(width);
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

void Painter::alphablend(int x, int y, float alpha, QColor color) {
    if(x < 0 || y < 0 || x >= mImage->width() || y >= mImage->height())
        return;
    alpha *= color.alphaF();
    QRgb c = mImage->pixel(x, y);
    color.setRed(qRed(c) * (1 - alpha) + color.red() * alpha);
    color.setGreen(qGreen(c) * (1 - alpha) + color.green() * alpha);
    color.setBlue(qBlue(c) * (1 - alpha) + color.blue() * alpha);
    drawPixel(x, y, color);
}

float Painter::capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r) {
    float pax = px - ax, pay = py - ay, bax = bx - ax, bay = by - ay;
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx = pax - bax * h, dy = pay - bay * h;
    return sqrtf(dx * dx + dy * dy) - r;
}

float Painter::circleSDF(float px, float py,float x, float y, float r, float width) {
    width /= 2;
    float pr = sqrtf((px - x) * (px - x) + (py - y) * (py - y));
    if (pr > r + width)
        return pr - r + width;
    else if (pr < r - width)
        return r - width - pr;
    else
        return fminf(pr - r + width, r + width - pr);
}

void Painter::lineSDFAABB(float ax, float ay, float bx, float by, float r, QColor color) {
    int x0 = (int)floorf(fminf(ax, bx) - r);
    int x1 = (int) ceilf(fmaxf(ax, bx) + r);
    int y0 = (int)floorf(fminf(ay, by) - r);
    int y1 = (int) ceilf(fmaxf(ay, by) + r);
    // TODO: optimize
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            alphablend(x, y, fmaxf(fminf(0.5f - capsuleSDF(x, y, ax, ay, bx, by, r / 2), 1.0f), 0.0f), color);
}

void Painter::circleSDFAABB(float ax, float ay, float radius, float width, QColor color) {
    int x0 = (int)floorf(ax - radius - width);
    int y0 = (int)floorf(ay - radius - width);
    int x1 = (int) ceilf(ax + radius + width);
    int y1 = (int) ceilf(ay + radius + width);
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            alphablend(x, y, fmaxf(fminf(0.5f - circleSDF(x, y, ax, ay, radius, width), 1.0f), 0.0f), color);
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
