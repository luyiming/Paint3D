#include "circleinstrument.h"
#include "../drawingboard.h"
#include <QPen>
#include <QPainter>

CircleInstrument::CircleInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}


void CircleInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton) {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        mImageCopy = QImage(*board.getImage());
    }
}

void CircleInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
    }
}

void CircleInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}


void CircleInstrument::draw(DrawingBoard &board)
{
    board.setImage(mImageCopy);
    QPainter painter(board.getImage());

    QBrush brush(board.fillColor());
    if (board.fillStyle() == 'None') {
        brush.setStyle(Qt::NoBrush);
    }
    else {
        brush.setStyle(Qt::SolidPattern);
    }

    QPen pen(brush, board.thickness());
    pen.setColor(board.borderColor());
    if (board.borderStyle() == 'None') {
        pen.setStyle(Qt::NoPen);
    }
    else {
        pen.setStyle(Qt::SolidLine);
    }

    painter.setPen(pen);

    if(mStartPoint != mEndPoint)
    {
        painter.drawEllipse((mStartPoint.x() + mEndPoint.x()) / 2, (mStartPoint.y() + mEndPoint.y()) / 2,
                            abs(mStartPoint.x() - mEndPoint.x()), abs(mStartPoint.y() - mEndPoint.y()));
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }

    painter.end();

    board.update();
}
