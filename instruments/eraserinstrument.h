#ifndef ERASERINSTRUMENT_H
#define ERASERINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>

class EraserInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit EraserInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);
};

#endif // ERASERINSTRUMENT_H
