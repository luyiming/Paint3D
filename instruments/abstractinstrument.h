#ifndef ABSTRACTINSTRUMENT_H
#define ABSTRACTINSTRUMENT_H

#include <QObject>
#include <QMouseEvent>
#include <QImage>

class DrawingBoard;

class AbstractInstrument : public QObject
{
    Q_OBJECT
public:
    explicit AbstractInstrument(QObject *parent = NULL);

public:
    virtual void mousePressEvent(QMouseEvent *event, DrawingBoard &board) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board) = 0;
    virtual void draw(DrawingBoard &board) = 0;

protected:
    QPoint mStartPoint, mEndPoint;
    QImage mImageCopy; /**< Image for storing copy of current image on DrawingBoard, needed for some instruments. */

    virtual void makeUndoCommand(DrawingBoard &board);
};

#endif // ABSTRACTINSTRUMENT_H
