#include "drawingboard.h"

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include "instruments/pixelinstrument.h"
#include "instruments/lineinstrument.h"
#include "instruments/circleinstrument.h"

DrawingBoard::DrawingBoard(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_instrumentHandlers.fill(NULL, (int)INSTRUMENTS_COUNT);
    m_instrumentHandlers[BRUSH_PIXEL] = new PixelInstrument(this);
    m_instrumentHandlers[SHAPE_LINE] = new LineInstrument(this);
    m_instrumentHandlers[SHAPE_CIRCLE] = new CircleInstrument(this);
}

void DrawingBoard::handleMousePress(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonPress, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        m_instrumentHandlers[m_instrument]->mousePressEvent(&event, *this);
    }
    //  qDebug() <<"new mouse pressed" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseRelease(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseButtonRelease, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        m_instrumentHandlers[m_instrument]->mouseReleaseEvent(&event, *this);
    }
    //   qDebug() <<"new mouse release" << event.pos() << event.buttons();
}

void DrawingBoard::handleMouseMove(int x, int y, int button, int buttons, int modifiers) {
    QMouseEvent event(QEvent::MouseMove, QPoint(x, y), (Qt::MouseButton)button, (Qt::MouseButtons)buttons, (Qt::KeyboardModifiers)modifiers);
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        m_instrumentHandlers[m_instrument]->mouseMoveEvent(&event, *this);
    }
    //  qDebug() <<"new mouse move" << event.pos() << event.buttons();
}

void DrawingBoard::paint(QPainter *painter){
    if (m_image == nullptr) {
        m_image = new QImage(width(), height(), QImage::Format_ARGB32);
        QPainter *painter = new QPainter(m_image);
        painter->fillRect(0, 0, m_image->width(), m_image->height(), Qt::white);
        painter->end();
    }

    painter->drawImage(QPoint(0, 0), *m_image);
}
