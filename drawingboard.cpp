#include "drawingboard.h"

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include "instruments/pixelinstrument.h"
#include "instruments/lineinstrument.h"
#include "instruments/circleinstrument.h"
#include "instruments/squareinstrument.h"
#include "instruments/roundedsquareinstrument.h"
#include "instruments/fillinstrument.h"
#include "instruments/eraserinstrument.h"
#include "instruments/polygoninstrument.h"

DrawingBoard::DrawingBoard(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    m_instrumentHandlers.fill(NULL, (int)INSTRUMENTS_COUNT);
    m_instrumentHandlers[BRUSH_PIXEL] = new PixelInstrument(this);
    m_instrumentHandlers[BRUSH_FILL] = new FillInstrument(this);
    m_instrumentHandlers[BRUSH_ERASER] = new EraserInstrument(this);
    m_instrumentHandlers[SHAPE_LINE] = new LineInstrument(this);
    m_instrumentHandlers[SHAPE_CIRCLE] = new CircleInstrument(this);
    m_instrumentHandlers[SHAPE_SQUARE] = new SquareInstrument(this);
    m_instrumentHandlers[SHAPE_ROUNDED_SQUARE] = new RoundedSquareInstrument(this);
    m_instrumentHandlers[VECTOR_POLYGON] = new PolygonInstrument(this);
    ((PolygonInstrument*)m_instrumentHandlers[VECTOR_POLYGON])->setBoard(*this);

    mUndoStack = new QUndoStack(this);
    mUndoStack->setUndoLimit(100);

    QObject::connect(mUndoStack, &QUndoStack::canUndoChanged, this, &DrawingBoard::canUndoChanged);
    QObject::connect(mUndoStack, &QUndoStack::canRedoChanged, this, &DrawingBoard::canRedoChanged);
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

        m_vector_image = new QImage(width(), height(), QImage::Format_ARGB32);
//        painter = new QPainter(m_vector_image);
//        painter->fillRect(0, 0, m_vector_image->width(), m_vector_image->height(), Qt::white);
//        painter->end();
    }

    QImage blend_image = *m_image;
//    QPainter *img_painter = new QPainter(&blend_image);
//    img_painter->drawImage(QPoint(0, 0), *m_image);
//    img_painter->drawImage(QPoint(0, 0), *m_vector_image);

    for (int x = 0; x < m_image->width(); x++) {
        for (int y = 0; y < m_image->height(); y++) {
            QRgb r1 = m_image->pixel(x, y);
            QRgb r2 = m_vector_image->pixel(x, y);
            QColor color(
                qRed(r1) * (1 - qAlpha(r2) / 255) + qRed(r2) * (qAlpha(r2) / 255),
                qGreen(r1) * (1 - qAlpha(r2) / 255) + qGreen(r2) * (qAlpha(r2) / 255),
                qBlue(r1) * (1 - qAlpha(r2) / 255) + qBlue(r2) * (qAlpha(r2) / 255),
                        255);
            blend_image.setPixel(x, y, color.rgb());
        }
    }
      painter->drawImage(QPoint(0, 0), blend_image);

//    painter->drawImage(QPoint(0, 0), *m_vector_image);


}

void DrawingBoard::pushUndoCommand(UndoCommand *command) {
    if (command != NULL)
        mUndoStack->push(command);
}

void DrawingBoard::undoRequest() {
//    qDebug() << "undo count: " << mUndoStack->count();
    mUndoStack->undo();
}

void DrawingBoard::redoRequest() {
//    qDebug() << "redo count: " << mUndoStack->count();
    mUndoStack->redo();
}

void DrawingBoard::startClip()  {
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->startClip();
    }
}

void DrawingBoard::endClip()  {
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->endClip(*this);
    }
}


void DrawingBoard::rotateShape(float angle) {
    m_rotate_angle = angle;
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->rotate(angle, *this);
    }
}

void DrawingBoard::scaleShape(float factor) {
    m_scale_factor = factor;
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->scale(factor, *this);
    }
}

void DrawingBoard::setCurveMode(int curve_points) {
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->setCurveMode(curve_points);
    }
}

void DrawingBoard::setPolygonMode() {
    if (m_instrument != VECTOR_POLYGON) {
        qDebug() << "not in polygon mode, error";
        return;
    }
    if (m_instrument != INSTRUMENT_NONE && m_instrumentHandlers[m_instrument] != NULL) {
        PolygonInstrument* intr = (PolygonInstrument*)m_instrumentHandlers[m_instrument];
        intr->setPolygonMode();
    }
}

void DrawingBoard::openFile(QString filePath) {
    QImage image(QUrl(filePath).toLocalFile());
    if (m_image == NULL) {
        m_image = new QImage(width(), height(), QImage::Format_ARGB32);
    }
//    image.scaled(width(), height());
    QPainter painter(m_image);
    painter.drawImage(0, 0, image);
//    *m_image = image;
    painter.end();
    this->update();
//    qDebug() << filePath;
}

void DrawingBoard::saveFile(QString filePath) {
    qDebug() << filePath;

    QImage blend_image = *m_image;
    for (int x = 0; x < m_image->width(); x++) {
        for (int y = 0; y < m_image->height(); y++) {
            QRgb r1 = m_image->pixel(x, y);
            QRgb r2 = m_vector_image->pixel(x, y);
            QColor color(
                qRed(r1) * (1 - qAlpha(r2) / 255) + qRed(r2) * (qAlpha(r2) / 255),
                qGreen(r1) * (1 - qAlpha(r2) / 255) + qGreen(r2) * (qAlpha(r2) / 255),
                qBlue(r1) * (1 - qAlpha(r2) / 255) + qBlue(r2) * (qAlpha(r2) / 255),
                        255);
            blend_image.setPixel(x, y, color.rgb());
        }
    }
    bool succ = blend_image.save(QUrl(filePath).toLocalFile() + QDir::separator() + "test.png");
    qDebug() << succ;
}
