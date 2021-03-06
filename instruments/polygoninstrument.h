#ifndef POLYGONINSTRUMENT_H
#define POLYGONINSTRUMENT_H

#include "abstractinstrument.h"
#include "drawingboard.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QRect>
#include <QDebug>

class PolygonInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit PolygonInstrument(QObject *parent = NULL);
    void setBoard(DrawingBoard &board) {
        m_board = &board;
    }

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);

    void setIsSelected(bool isSelected) {
        m_select_mode = isSelected;
        if (current_shape == SHAPE_POLYGON) {
            m_board->canClip(isSelected);
        }
        if (isSelected == false || (m_select_mode != isSelected && isSelected == true)) {
            m_board->resetRotateAngle();
            m_board->resetScaleFactor();
        }
        m_board->showRotateAndScale(isSelected);
    }
    bool isSelected() { return m_select_mode; }

    void setIsClipMode(bool isClipMode) { m_clip_mode = isClipMode; }
    bool isClipMode() { return m_clip_mode; }

    void startClip() { if (isSelected()) m_clip_mode = true; }
    void endClip(DrawingBoard &board);

    void rotate(float angle, DrawingBoard &board);
    void scale(float factor, DrawingBoard &board);

    void setCurveMode(int curve_points);
    void setPolygonMode() { qDebug() <<"polygon"; current_shape = SHAPE_POLYGON; }

    void fillBgColor(QList<QPoint> &points, QImage *image, QColor color);

    void setFillColor(bool fillColor, QColor color) {
        hasFillColor = fillColor;
        bgColor = color;
        this->draw(*m_board);
    }

    void finishPaint(DrawingBoard &board);

private:
    QPoint m_clipStart, m_clipEnd;
    int m_selectRange = 10; // 5px
    bool m_select_mode = false;
    bool m_clip_mode = false;
    bool m_hasClipBox = false;
    QRect m_selectBox;
    QRect m_clipBox;

    QList<QList<QPoint>> m_polygons;
    struct ColorNode {
        QColor color; bool hasFillColor;
        ColorNode(QColor color, bool b) : color(color), hasFillColor(b) {}
    };
    QList<ColorNode> m_polygons_color;

    QList<QList<QPoint>> m_curves;

    enum { SHAPE_POLYGON, SHAPE_CURVE3, SHAPE_CURVE4, SHAPE_CURVE5, SHAPE_NONE } current_shape = SHAPE_NONE;
    QList<QPoint> m_points;
    QList<QPoint> m_translate_points;

    QPoint m_center_point;

    bool isDragPointMode = false;
    bool isDragCenterMode = false;
    bool isDragShapeMode = false;
    QPoint drag_lasts_pos;
    int dragPointIndex = 0;

    bool hasFillColor = false;
    QColor bgColor;

    DrawingBoard *m_board = NULL;
};

#endif // POLYGONINSTRUMENT_H
