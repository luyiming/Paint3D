#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>
#include <QList>
#include "instrumentsenum.h"

class AbstractInstrument;

class DrawingBoard : public QQuickPaintedItem
{
    Q_OBJECT

public:
    DrawingBoard(QQuickItem *parent = 0);
    void paint(QPainter *painter);

public:
    Q_INVOKABLE void handleMousePress(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseRelease(int x, int y, int button, int buttons, int modifiers);
    Q_INVOKABLE void handleMouseMove(int x, int y, int button, int buttons, int modifiers);

public:
    void setIsInPaint(bool isInPaint) { mIsInPaint = isInPaint; }
    bool isInPaint() { return mIsInPaint; }
    QImage* getImage() { return m_image; }

private:
    QImage *m_image = nullptr;
    bool mIsInPaint = false;
    QVector<AbstractInstrument*> mInstrumentsHandlers;
};

#endif // DRAWINGBOARD_H
