#ifndef ROUNDEDSQUAREINSTRUMENT_H
#define ROUNDEDSQUAREINSTRUMENT_H

#include <QObject>
#include "abstractinstrument.h"

class DrawingBoard;

class RoundedSquareInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit RoundedSquareInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // ROUNDEDSQUAREINSTRUMENT_H
