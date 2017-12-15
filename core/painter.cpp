#include "painter.h"
#include <QImage>

namespace CorePainter {

Painter::Painter(QImage *image, QObject *parent) : QObject(parent)
{
    mImage = image;
}

void Painter::drawPixel(int x, int y, const QColor & color)
{
    if(x >= 0 && y >= 0 && x < mImage->width() && y < mImage->height()) {
        QRgb *rowData = (QRgb*)mImage->scanLine(y);
        rowData[x] = color.rgb();
//        mImage->setPixel(x, y, color.rgb());
    }
}

void Painter::drawLine(const QPoint & p1, const QPoint & p2, int width, float opacity, QColor color)
{
//    drawLineBresenham(p1.x(), p1.y(), p2.x(), p2.y(), color);
    color.setAlphaF(opacity);
    drawLineSDFAABB(p1.x(), p1.y(), p2.x(), p2.y(), width, color);
}

void Painter::drawPoint(const QPoint & position, int width, float opacity, QColor color)
{
    drawCircle(position.x(), position.y(), width / 2.0, 0, opacity, color, color, false, true);
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

void Painter::drawSquare(int x, int y, int width, int height, int thickness, float opacity, QColor fg, QColor bg, bool usefg, bool usebg) {
    float w = width / 2.0;
    float h = height / 2.0;
    float ax = x + w;
    float ay = y + h;
    for (int px = x - 2; px <= x + width + 2; px++)
        for (int py = y - 2; py <= y + height + 2; py++) {
            if(px < 0 || py < 0 || px >= mImage->width() || py >= mImage->height())
                continue;
            QRgb *rowData = (QRgb*)mImage->scanLine(py);
            QRgb pixelData = rowData[px];
//            QRgb pixelData = mImage->pixel(px, py);
            QColor color = alphablend(squareSDF(px, py, ax, ay, w, h), thickness / 2.0, 0.5, opacity, fg.rgba(), bg.rgba(), pixelData, usefg, usebg);
            drawPixel(px, py, color);
        }
}

void Painter::drawRoundedSquare(int x, int y, int width, int height, int radius, int thickness, float opacity, QColor fg, QColor bg, bool usefg, bool usebg) {
    float w = width / 2.0;
    float h = height / 2.0;
    float ax = x + w;
    float ay = y + h;
    for (int px = x - 2; px <= x + width + 2; px++)
        for (int py = y - 2; py <= y + height + 2; py++) {
            if(px < 0 || py < 0 || px >= mImage->width() || py >= mImage->height())
                continue;
            QRgb *rowData = (QRgb*)mImage->scanLine(py);
            QRgb pixelData = rowData[px];
            QColor color = alphablend(roundedSquareSDF(px, py, ax, ay, w, h, radius), thickness / 2.0, 0.5, opacity, fg.rgba(), bg.rgba(), pixelData, usefg, usebg);
            drawPixel(px, py, color);
        }
}

void Painter::drawCircle(int x, int y, int radius, int thickness, float opacity, QColor fg, QColor bg, bool usefg, bool usebg) {
    for (int px = x - radius - 2; px <= x + radius + 2; px++)
        for (int py = y - radius - 2; py <= y + radius + 2; py++) {
            if(px < 0 || py < 0 || px >= mImage->width() || py >= mImage->height())
                continue;
            QRgb *rowData = (QRgb*)mImage->scanLine(py);
            QRgb pixelData = rowData[px];
            QColor color = alphablend(circleSDF(px, py, x, y, radius), thickness / 2.0, 0.5, opacity, fg.rgba(), bg.rgba(), pixelData, usefg, usebg);
            drawPixel(px, py, color);
        }
}

void Painter::drawEllipse(int x, int y, int rx, int ry, int thickness, float opacity, QColor fg, QColor bg, bool usefg, bool usebg) {
    Q_UNUSED(thickness);
    Q_UNUSED(opacity);
    Q_UNUSED(bg);
    Q_UNUSED(usefg);
    Q_UNUSED(usebg);
    drawEllipseBresenham(x, y, rx, ry, fg);
//    for (int px = x - rx - 2; px <= x + rx + 2; px++)
//        for (int py = y - ry - 2; py <= y + ry + 2; py++) {
//            if(px < 0 || py < 0 || px >= mImage->width() || py >= mImage->height())
//                continue;
//            QRgb *rowData = (QRgb*)mImage->scanLine(py);
//            QRgb pixelData = rowData[px];
//            QColor color = alphablend(ellipseSDF(px, py, x, y, rx, ry), thickness / 2.0, 0.5, opacity, fg.rgba(), bg.rgba(), pixelData, usefg, usebg);
//            drawPixel(px, py, color);
//        }
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

QColor Painter::alphablend(float d, float w, float a, float o, QRgb fg, QRgb bg, QRgb color, bool usefg, bool usebg) {
    float bg_alpha = 0.0, fg_alpha = 0.0;
    if (usebg)
        bg_alpha = fmaxf(fminf(- 0.5 * (d + w - a) / a, 1.0f), 0.0f) * o;
    if (usefg)
        fg_alpha = d > 0 ? fmaxf(fminf(- 0.5 * (d - w - a) / a, 1.0f), 0.0f) * o : fmaxf(fminf(0.5 * (d + w + a) / a, 1.0f), 0.0f) * o;
    QColor result;
    result.setRed(qRed(fg) * fg_alpha + qRed(bg) * bg_alpha + qRed(color) * (1 - fg_alpha - bg_alpha));
    result.setGreen(qGreen(fg) * fg_alpha + qGreen(bg) * bg_alpha + qGreen(color) * (1 - fg_alpha - bg_alpha));
    result.setBlue(qBlue(fg) * fg_alpha + qBlue(bg) * bg_alpha + qBlue(color) * (1 - fg_alpha - bg_alpha));
    result.setAlphaF(1.0);
    return result;
}

float Painter::capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r) {
    float pax = px - ax, pay = py - ay, bax = bx - ax, bay = by - ay;
    float h = fmaxf(fminf((pax * bax + pay * bay) / (bax * bax + bay * bay), 1.0f), 0.0f);
    float dx = pax - bax * h, dy = pay - bay * h;
    return sqrtf(dx * dx + dy * dy) - r;
}

float Painter::circleSDF(float px, float py,float x, float y, float r) {
    float pr = sqrtf((px - x) * (px - x) + (py - y) * (py - y));
    return pr - r;
}

float Painter::ellipseSDF(float px, float py, float ax, float ay, float rx, float ry)
{
    float rx2 = rx * rx;
    float ry2 = ry * ry;
    return (ry2 * (px - ax) * (px - ax) + rx2 * (py - ay) * (py - ay) - rx2 * ry2) / (rx2 * ry2);
}

float Painter::squareSDF(float px, float py, float ax, float ay, float width, float height)
{
    float dx = abs(px - ax) - width;
    float dy = abs(py - ay) - height;
//    return fmaxf(dx, dy);
    return fminf(fmaxf(dx, dy), 0.0) + sqrtf(fmaxf(dx, 0.0) * fmaxf(dx, 0.0) + fmaxf(dy, 0.0) * fmaxf(dy, 0.0));
}

float Painter::roundedSquareSDF(float px, float py, float ax, float ay, float width, float height, float r)
{
    float dx = abs(px - ax) - width;
    float dy = abs(py - ay) - height;
    return fminf(fmaxf(dx, dy), 0.0) + sqrtf(fmaxf(dx, 0.0) * fmaxf(dx, 0.0) + fmaxf(dy, 0.0) * fmaxf(dy, 0.0)) - r;
}

void Painter::drawLineSDFAABB(float ax, float ay, float bx, float by, float r, QColor color) {
    int x0 = (int)floorf(fminf(ax, bx) - r);
    int x1 = (int) ceilf(fmaxf(ax, bx) + r);
    int y0 = (int)floorf(fminf(ay, by) - r);
    int y1 = (int) ceilf(fmaxf(ay, by) + r);
    // TODO: optimize
    for (int y = y0; y <= y1; y++)
        for (int x = x0; x <= x1; x++)
            alphablend(x, y, fmaxf(fminf(0.5f - capsuleSDF(x, y, ax, ay, bx, by, r / 2), 1.0f), 0.0f), color);
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

void Painter::drawEllipseBresenham(int x1, int y1, int rx, int ry, QColor color) {
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
