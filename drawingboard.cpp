#include "drawingboard.h"

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include "instruments/pixelinstrument.h"

DrawingBoard::DrawingBoard(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    mInstrumentsHandlers.fill(nullptr, (int)INSTRUMENTS_COUNT);
    mInstrumentsHandlers[PIXEL] = new PixelInstrument(this);
}

void DrawingBoard::handleMousePress(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonPress, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    mInstrumentsHandlers[PIXEL]->mousePressEvent(&event, *this);
//  qDebug() <<"new mouse pressed" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseRelease(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonRelease, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    mInstrumentsHandlers[PIXEL]->mouseReleaseEvent(&event, *this);
//   qDebug() <<"new mouse release" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseMove(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseMove, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    mInstrumentsHandlers[PIXEL]->mouseMoveEvent(&event, *this);
//  qDebug() <<"new mouse move" << event.pos() << event.buttons();
}

void DrawingBoard::paint(QPainter *painter){
    if (m_image == nullptr) {
        m_image = new QImage(width(), height(), QImage::Format_RGB32);
        QPainter *painter = new QPainter(m_image);
        painter->fillRect(0, 0, m_image->width(), m_image->height(), Qt::white);
        painter->end();
    }

    painter->drawImage(QPoint(0, 0), *m_image);

//    qDebug() <<"paint";
}
