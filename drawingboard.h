#ifndef DRAWINGBOARD_H
#define DRAWINGBOARD_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QBrush>
#include <QObject>
#include <QDebug>
#include <QMouseEvent>
#include <QList>
#include <QString>
#include <QUndoStack>
#include <QPoint>
#include "undocommand.h"

class AbstractInstrument;
extern QStringList vectorModel; // main.cpp
void notifyModel();

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
    Q_INVOKABLE void undoRequest();
    Q_INVOKABLE void redoRequest();
    Q_PROPERTY(InstrumentType instrument READ instrument WRITE setInstrument)
    Q_PROPERTY(int thickness READ thickness WRITE setThickness)
    Q_PROPERTY(int opaqueness READ opaqueness WRITE setOpaqueness)
    Q_PROPERTY(QColor brushColor READ brushColor WRITE setBrushColor)

    Q_PROPERTY(QColor borderColor MEMBER m_borderColor)
    Q_PROPERTY(QColor fillColor MEMBER m_fillColor)
    Q_PROPERTY(QString borderStyle MEMBER m_borderStyle)
    Q_PROPERTY(QString fillStyle MEMBER m_fillStyle)

    Q_PROPERTY(bool canUndo READ canUndo NOTIFY canUndoChanged)
    Q_PROPERTY(bool canRedo READ canRedo NOTIFY canRedoChanged)

    Q_INVOKABLE void rotateShape(float angle);
    Q_INVOKABLE void scaleShape(float factor);
    Q_INVOKABLE void setCurveMode(int curve_points);
    Q_INVOKABLE void setPolygonMode();

//    Q_INVOKABLE void saveToFile(QUrl filepath);
//    Q_INVOKABLE void readFromFile(QUrl filepath);


signals:
    void canUndoChanged();
    void canRedoChanged();

public:
    enum InstrumentType {
        INSTRUMENT_NONE = 0,
        BRUSH_PIXEL,
        SHAPE_LINE,
        SHAPE_CIRCLE,
        SHAPE_SQUARE,
        SHAPE_ROUNDED_SQUARE,
        BRUSH_FILL,
        BRUSH_ERASER,
        VECTOR_POLYGON,


        // Don't use it. (Used to know count of instruments)
        INSTRUMENTS_COUNT
    };
    Q_ENUM(InstrumentType)

public:
    void setIsInPaint(bool isInPaint) { m_isInPaint = isInPaint; }
    bool isInPaint() { return m_isInPaint; }
    QImage* getImage() { return m_image; }
    void setImage(const QImage &image) { *m_image = image; }
    QImage* getVectorImage() { return m_vector_image; }
    void setVectorImage(const QImage &image) { *m_vector_image = image; }
    InstrumentType instrument() { return m_instrument; }
    void setInstrument(InstrumentType instrument) { m_instrument = instrument; qDebug() << instrument;}
    int thickness() { return m_thickness; }
    void setThickness(int thickness) { m_thickness = thickness; qDebug() << thickness; }
    int opaqueness() { return m_opaqueness; }
    void setOpaqueness(int opaqueness) { m_opaqueness = opaqueness; qDebug() << opaqueness; }
    QColor brushColor() { return m_brushColor; }
    void setBrushColor(QColor brushColor) { m_brushColor = brushColor; qDebug() << brushColor; }
    QColor borderColor() { return m_borderColor; }
    QColor fillColor() { return m_fillColor; }
    QString borderStyle() { return m_borderStyle; }
    QString fillStyle() { return m_fillStyle; }
    void pushUndoCommand(UndoCommand *command);
    bool canUndo() { return mUndoStack->canUndo(); }
    bool canRedo() { return mUndoStack->canRedo(); }

private:
    QImage *m_image = nullptr;
    QImage *m_vector_image = nullptr;
    bool m_isInPaint = false;

    int m_thickness = 1;
    int m_opaqueness = 100; // 1~100
    QColor m_borderColor, m_fillColor;
    QString m_borderStyle, m_fillStyle;

    QColor m_brushColor = Qt::black;
    QVector<AbstractInstrument*> m_instrumentHandlers;
    InstrumentType m_instrument = INSTRUMENT_NONE;

    QUndoStack *mUndoStack;

private:
    QStringList m_vectorDataList;
    QList<QList<QPoint>> m_vector_shapes;

public:
    void addPolygon(QList<QPoint> polygon) {
        m_vector_shapes.append(polygon);
        vectorModel.append("polygon");
        notifyModel();
    }

    void addCurve(QList<QPoint> curve) {
        m_vector_shapes.append(curve);
        vectorModel.append("curve");
        notifyModel();
    }

    Q_INVOKABLE void startClip();
    Q_INVOKABLE void endClip();

    float m_rotate_angle = 0.0f;
    float m_scale_factor = 1.0f;
    float getRotateAngle() { return m_rotate_angle; }
    float getScaleFactor() { return m_scale_factor; }
    void resetRotateAngle() { m_rotate_angle = 0.0f; }
    void resetScaleFactor() { m_scale_factor = 1.0f; }

    Q_INVOKABLE void openFile(QString filePath);
    Q_INVOKABLE void saveFile(QString filePath);

signals:
    void resetScaleAndRotateChanged();
    bool canClip(bool can);
    bool showRotateAndScale(bool show);
};

#endif // DRAWINGBOARD_H
