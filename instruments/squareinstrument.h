#ifndef SQUAREINSTRUMENT_H
#define SQUAREINSTRUMENT_H

#include <QObject>
#include "abstractinstrument.h"

class SquareInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit SquareInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // SQUAREINSTRUMENT_H
