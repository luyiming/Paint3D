#ifndef FILLINSTRUMENT_H
#define FILLINSTRUMENT_H

#include <QObject>
#include "abstractinstrument.h"

class FillInstrument : public AbstractInstrument
{
    Q_OBJECT
public:
    explicit FillInstrument(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);

private:
    void fillAux(int x, int y, QRgb switchColor, QRgb oldColor, QImage &tempImage);
};


#endif // FILLINSTRUMENT_H
