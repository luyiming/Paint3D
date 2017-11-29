#include "lineinstrument.h"
#include "../drawingboard.h"
#include <QPen>
#include <QPainter>

LineInstrument::LineInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}


void LineInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton) {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        mImageCopy = QImage(*board.getImage());
        makeUndoCommand(board);
    }
}

void LineInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
    }
}

void LineInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}


void LineInstrument::draw(DrawingBoard &board)
{
    board.setImage(mImageCopy);
    QPainter painter(board.getImage());

//    painter.setPen(QPen(Qt::black));
    painter.setPen(QPen(board.borderColor(), board.thickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.setOpacity(board.opaqueness() / 100.0);

    if(mStartPoint != mEndPoint)
    {
        painter.drawLine(mStartPoint, mEndPoint);
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }

    painter.end();

    board.update();
}
