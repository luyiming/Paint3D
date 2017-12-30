#ifndef POLYGONINSTRUMENT_H
#define POLYGONINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>

class PolygonInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit PolygonInstrument(QObject *parent = NULL);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // POLYGONINSTRUMENT_H
