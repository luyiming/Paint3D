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
    void drawLine(const QPoint & p1, const QPoint & p2, QColor color = Qt::black, int width = 1, bool useBresenham = false);
    void drawPoint(const QPoint & position, int width = 1);
    void drawCircle(int x1, int y1, int r, QColor color) { drawCircleBresenham(x1, y1, r, color); }

private:
    void drawPixel(int x, int y, const QColor & color);
    void drawLineDDA(int x1, int y1, int x2, int y2, QColor color);
    void drawLineBresenham(int x1, int y1, int x2, int y2, QColor color);
    void drawCircleBresenham(int x1, int y1, int r, QColor color);

    // rx: x轴方向长半轴 (rx, 0)
    // ry: y轴方向短半轴 (0, ry)
    void drawEllipse(int x1, int y1, int rx, int ry, QColor color);

    void alphablend(int x, int y, float alpha, QColor color);
    float capsuleSDF(float px, float py, float ax, float ay, float bx, float by, float r);
    float circleSDF(float px, float py,float x, float y, float r, float width);
    void lineSDFAABB(float ax, float ay, float bx, float by, float r, QColor color);
    void circleSDFAABB(float x, float y, float radius, float width, QColor color);

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
