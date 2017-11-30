#include "eraserinstrument.h"
#include "../drawingboard.h"
#include "core/painter.h"
#include <QPen>
#include <QPainter>

EraserInstrument::EraserInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void EraserInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton)
    {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        makeUndoCommand(board);
    }
}

void EraserInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint())
    {
        mEndPoint = event->pos();
        draw(board);
        mStartPoint = event->pos();
    }
}

void EraserInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint())
    {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}

void EraserInstrument::draw(DrawingBoard &board)
{
    QPainter painter(board.getImage());
    painter.setPen(QPen(Qt::white, board.thickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing);

    CorePainter::Painter mypainter(board.getImage());
    if(mStartPoint != mEndPoint) {
//        painter.drawLine(mStartPoint, mEndPoint);
        mypainter.drawLine(mStartPoint, mEndPoint, board.thickness(), board.opaqueness() / 100.0, Qt::white);
    }

    if(mStartPoint == mEndPoint) {
//        painter.drawPoint(mStartPoint);
        mypainter.drawPoint(mEndPoint, board.thickness(), board.opaqueness() / 100.0, Qt::white);
    }

    painter.end();
    board.update();
}
