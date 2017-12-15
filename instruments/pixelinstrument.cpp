#include "pixelinstrument.h"
#include "../drawingboard.h"
#include "core/painter.h"
#include <QPen>
#include <QPainter>

PixelInstrument::PixelInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}

void PixelInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton) {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        makeUndoCommand(board);
    }
}

void PixelInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        mStartPoint = event->pos();
    }
}

void PixelInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}

void PixelInstrument::draw(DrawingBoard &board)
{
    QPainter painter(board.getImage());
    painter.setPen(QPen(board.brushColor(), board.thickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setOpacity(board.opaqueness() / 100.0);

    if (board.thickness() > 5)
        painter.setRenderHint(QPainter::Antialiasing);

    CorePainter::Painter mypainter(board.getImage());

    if(mStartPoint != mEndPoint)
    {
//        painter.drawLine(mStartPoint, mEndPoint);
        mypainter.drawLine(mStartPoint, mEndPoint, board.thickness(), board.opaqueness() / 100.0, board.brushColor());
    }

    if(mStartPoint == mEndPoint)
    {
//        painter.drawPoint(mStartPoint);
        mypainter.drawPoint(mEndPoint, board.thickness(), board.opaqueness() / 100.0, board.brushColor());
    }

    painter.end();

    board.update();
}
