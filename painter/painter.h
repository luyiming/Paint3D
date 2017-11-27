#ifndef PAINTER_H
#define PAINTER_H

#include <QObject>
#include <QImage>

class Painter : public QObject
{
    Q_OBJECT
public:
    explicit Painter(QImage *image, QObject *parent = nullptr);
    void drawLine(const QPoint & p1, const QPoint & p2);
    void drawPoint(const QPoint & position);

private:
    void setPixel(int x, int y, const QColor & color);

private:
    QImage *m_image = nullptr;
};

#endif // PAINTER_H
