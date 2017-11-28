#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>
#include <QList>

class AbstractInstrument;

class DrawingBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    DrawingBoard(QQuickItem *parent = 0);

    // paint() will be called when update() is called
    void paint(QPainter *painter);

public:
    Q_INVOKABLE void handleMousePress(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseRelease(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseMove(int x, int y, int button, int buttons, int modifiers);
    Q_PROPERTY(InstrumentType instrument READ instrument WRITE setInstrument)

public:
    enum InstrumentType {
        INSTRUMENT_NONE = 0,
        BRUSH_PIXEL,
        SHAPE_LINE,

        // Don't use it. (Used to know count of instruments)
        INSTRUMENTS_COUNT
    };
    Q_ENUM(InstrumentType)

public:
    void setIsInPaint(bool isInPaint) { mIsInPaint = isInPaint; }
    bool isInPaint() { return mIsInPaint; }
    QImage* getImage() { return mImage; }
    InstrumentType instrument() { return mInstrument; }
    void setInstrument(InstrumentType instrument) { mInstrument = instrument; qDebug() <<instrument;}

private:
    QImage *mImage = nullptr;
    bool mIsInPaint = false;
    QVector<AbstractInstrument*> mInstrumentHandlers;
    InstrumentType mInstrument = INSTRUMENT_NONE;
};

#endif // DRAWINGBOARD_H
