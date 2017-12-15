#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QImage>

namespace CorePainter {

class Painter : public QObject
{
    Q_OBJECT

public:
    explicit Painter(QImage *image, QObject *parent = NULL);
    void drawLine(const QPoint & p1, const QPoint & p2, int width = 1, float opacity = 1.0, QColor color = Qt::black);
    void drawPoint(const QPoint & position, int width = 1, float opacity = 1.0, QColor color = Qt::black);
    void drawSquare(int x, int y, int width, int height, int thickness = 1, float opacity = 1.0, QColor fg = Qt::black, QColor bg = Qt::blue, bool usefg = true, bool usebg = false);
    void drawRoundedSquare(int x, int y, int width, int height, int radius, int thickness = 1, float opacity = 1.0, QColor fg = Qt::black, QColor bg = Qt::blue, bool usefg = true, bool usebg = false);
    void drawCircle(int x, int y, int radius, int thickness = 1, float opacity = 1.0, QColor fg = Qt::black, QColor bg = Qt::blue, bool usefg = true, bool usebg = false);
    void drawEllipse(int x, int y, int rx, int ry, int thickness = 1, float opacity = 1.0, QColor fg = Qt::black, QColor bg = Qt::blue, bool usefg = true, bool usebg = false);

private:
    void drawPixel(int x, int y, const QColor & color);

    void drawLineDDA(int x1, int y1, int x2, int y2, QColor color);
    void drawLineBresenham(int x1, int y1, int x2, int y2, QColor color);
    void drawCircleBresenham(int x1, int y1, int r, QColor color);


    // rx: x轴方向长半轴 (rx, 0)
    // ry: y轴方向短半轴 (0, ry)
    void drawEllipseBresenham(int x1, int y1, int rx, int ry, QColor color);

    void alphablend(int x, int y, float alpha, QColor color);

    QColor alphablend(float distance, float width, float antialias, float opacity, QRgb fg, QRgb bg, QRgb color, bool usefg = true, bool usebg = false);

    float capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r);
    float circleSDF(float px, float py,float x, float y, float r);
    float ellipseSDF(float px, float py, float ax, float ay, float rx, float ry);
    float squareSDF(float px, float py, float ax, float ay, float width, float height);
    float roundedSquareSDF(float px, float py, float ax, float ay, float width, float height, float r);

    void drawLineSDFAABB(float ax, float ay, float bx, float by, float r, QColor color);

private:
    QImage *mImage = NULL;

    void swap(int &a, int &b) {
        int t = a;
        a = b;
        b = t;
    }
};

}



#endif // PAINTER_H
