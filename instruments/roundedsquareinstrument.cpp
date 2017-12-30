#include "roundedsquareinstrument.h"
#include "../drawingboard.h"
#include <QPen>
#include <QPainter>

RoundedSquareInstrument::RoundedSquareInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}


void RoundedSquareInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton) {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        mImageCopy = QImage(*board.getImage());
        makeUndoCommand(board);
    }
}

void RoundedSquareInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
    }
}

void RoundedSquareInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}


void RoundedSquareInstrument::draw(DrawingBoard &board)
{
    board.setImage(mImageCopy);
    QPainter painter(board.getImage());

    QPen pen(board.borderColor(), board.thickness());
    if (board.borderStyle() == "None") {
        pen.setStyle(Qt::NoPen);
    }
    else if (board.borderStyle() == "Dash") {
        pen.setStyle(Qt::DashLine);
    }
    else if (board.borderStyle() == "Dot") {
        pen.setStyle(Qt::DotLine);
    }
    else if (board.borderStyle() == "DashDot") {
        pen.setStyle(Qt::DashDotLine);
    }
    else {
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);

    QBrush brush(board.fillColor());
    if (board.fillStyle() == "None") {
        brush.setStyle(Qt::NoBrush);
    }
    else {
        brush.setStyle(Qt::SolidPattern);
    }
    painter.setBrush(brush);

    painter.setOpacity(board.opaqueness() / 100.0);

    if(mStartPoint != mEndPoint)
    {
        painter.drawRoundedRect(QRect(mStartPoint, mEndPoint), 20, 20, Qt::RelativeSize);
    }

    painter.end();

    board.update();
}
