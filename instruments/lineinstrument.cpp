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
    }
}

void LineInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        mStartPoint = event->pos();
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
    QPainter painter(board.getImage());

    painter.setPen(QPen(Qt::black));

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
