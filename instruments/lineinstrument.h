#ifndef LINEINSTRUMENT_H
#define LINEINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>

class LineInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit LineInstrument(QObject *parent = NULL);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // LINEINSTRUMENT_H
