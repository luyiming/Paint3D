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
    }
}

void LineInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        board.setImage(mImageCopy);
        draw(board);
    }
}

void LineInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        board.setImage(mImageCopy);
        draw(board);
        board.setIsInPaint(false);
    }
}

void LineInstrument::draw(DrawingBoard &board)
{
    QPainter painter(board.getImage());

    painter.setPen(QPen(Qt::black));
//    painter.setPen(QPen(board.brushColor(), board.thickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

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
