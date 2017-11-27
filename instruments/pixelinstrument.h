#ifndef PIXELINSTRUMENT_H
#define PIXELINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>

class PixelInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit PixelInstrument(QObject *parent = nullptr);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);

protected:
    void paint(DrawingBoard &board);

};

#endif // PIXELINSTRUMENT_H
