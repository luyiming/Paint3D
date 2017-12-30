#include "fillinstrument.h"
#include "../drawingboard.h"

#include <QPen>
#include <QPainter>

FillInstrument::FillInstrument(QObject *parent) :
    AbstractInstrument(parent)
{
}

void FillInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    mStartPoint = mEndPoint = event->pos();
    board.setIsInPaint(true);
    makeUndoCommand(board);
}

void FillInstrument::mouseMoveEvent(QMouseEvent *, DrawingBoard &)
{

}

void FillInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    Q_UNUSED(event);
    if(board.isInPaint())
    {
        draw(board);
        board.setIsInPaint(false);
    }
}

void FillInstrument::draw(DrawingBoard &board)
{
    QColor fillColor = board.brushColor();

    QRgb pixel(board.getImage()->pixel(mStartPoint));
    QColor oldColor(pixel);

    if(fillColor != oldColor){
        fillAux(mStartPoint.x(), mStartPoint.y(), fillColor.rgb(), oldColor.rgb(), *board.getImage());
    }
    board.update();
}

void FillInstrument::fillAux(int x, int y, QRgb fillColor, QRgb oldColor, QImage &image)
{
    int temp_x(x), left_x(0);
    while(true)
    {
        if(image.pixel(temp_x, y) != oldColor)
            break;
        image.setPixel(temp_x, y, fillColor);
        if(temp_x > 0)
        {
            --temp_x;
            left_x = temp_x;
        }
        else
            break;
    }

    int right_x(0);
    temp_x = x + 1;
    while(true)
    {
        if(image.pixel(temp_x, y) != oldColor)
            break;
        image.setPixel(temp_x, y, fillColor);
        if(temp_x < image.width() - 1)
        {
            temp_x++;
            right_x = temp_x;
        }
        else
            break;
    }

    for(int x_ = left_x + 1; x_ < right_x; ++x_)
    {
        if(y < 1 || y >= image.height() - 1)
            break;
        if(right_x > image.width())
            break;
        QRgb currentColor = image.pixel(x_, y - 1);
        if(currentColor == oldColor && currentColor != fillColor)
            fillAux(x_, y - 1, fillColor, oldColor, image);
        currentColor = image.pixel(x_, y + 1);
        if(currentColor == oldColor && currentColor != fillColor)
            fillAux(x_, y + 1, fillColor, oldColor, image);
    }
}
