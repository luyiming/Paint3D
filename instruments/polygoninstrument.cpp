#include "polygoninstrument.h"
#include "../drawingboard.h"
#include "core/painter.h"
#include <QPen>
#include <QPainter>

PolygonInstrument::PolygonInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}


void PolygonInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton) {
        mStartPoint = mEndPoint = event->pos();
        board.setIsInPaint(true);
        mImageCopy = QImage(*board.getImage());
        makeUndoCommand(board);
    }
}

void PolygonInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
    }
}

void PolygonInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        draw(board);
        board.setIsInPaint(false);
    }
}


void PolygonInstrument::draw(DrawingBoard &board)
{
    board.setImage(mImageCopy);
    QPainter painter(board.getImage());
    painter.setPen(QPen(board.borderColor(), board.thickness(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setOpacity(board.opaqueness() / 100.0);

    CorePainter::Painter mypainter(board.getImage());

    if(mStartPoint != mEndPoint)
    {
//        painter.drawLine(mStartPoint, mEndPoint);
        QColor color = board.borderColor();
        color.setAlphaF(board.opaqueness() / 100.0);
        mypainter.drawLine(mStartPoint, mEndPoint, color, board.thickness());
    }

    if(mStartPoint == mEndPoint)
    {
        painter.drawPoint(mStartPoint);
    }

    painter.end();

    board.update();
}
