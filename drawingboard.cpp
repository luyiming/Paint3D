#include "drawingboard.h"

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include "instruments/pixelinstrument.h"

DrawingBoard::DrawingBoard(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    mInstrumentHandlers.fill(NULL, (int)INSTRUMENTS_COUNT);
    mInstrumentHandlers[BRUSH_PIXEL] = new PixelInstrument(this);
    mInstrument = BRUSH_PIXEL;
}

void DrawingBoard::handleMousePress(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonPress, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (mInstrument != INSTRUMENT_NONE) {
        mInstrumentHandlers[mInstrument]->mousePressEvent(&event, *this);
    }
    //  qDebug() <<"new mouse pressed" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseRelease(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonRelease, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (mInstrument != INSTRUMENT_NONE) {
        mInstrumentHandlers[mInstrument]->mouseReleaseEvent(&event, *this);
    }
    //   qDebug() <<"new mouse release" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseMove(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseMove, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (mInstrument != INSTRUMENT_NONE) {
        mInstrumentHandlers[mInstrument]->mouseMoveEvent(&event, *this);
    }
    //  qDebug() <<"new mouse move" << event.pos() << event.buttons();
}

void DrawingBoard::paint(QPainter *painter){
    if (mImage == nullptr) {
        mImage = new QImage(width(), height(), QImage::Format_RGB32);
        QPainter *painter = new QPainter(mImage);
        painter->fillRect(0, 0, mImage->width(), mImage->height(), Qt::white);
        painter->end();
    }

    painter->drawImage(QPoint(0, 0), *mImage);

//    qDebug() <<"paint";
}
