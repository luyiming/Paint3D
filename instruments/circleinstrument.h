#ifndef CIRCLEINSTRUMENT_H
#define CIRCLEINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>

class DrawingBoard;

class CircleInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit CircleInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // CIRCLEINSTRUMENT_H
