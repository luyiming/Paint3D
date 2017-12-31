#ifndef POLYGONINSTRUMENT_H
#define POLYGONINSTRUMENT_H

#include "abstractinstrument.h"
#include <QObject>
#include <QList>
#include <QPoint>
#include <QRect>

class PolygonInstrument : public AbstractInstrument
{
    Q_OBJECT

public:
    explicit PolygonInstrument(QObject *parent = NULL);

    void mousePressEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseMoveEvent(QMouseEvent *event, DrawingBoard &board);
    void mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board);
    void draw(DrawingBoard &board);

    void setIsSelected(bool isSelected) { m_select_mode = isSelected; }
    bool isSelected() { return m_select_mode; }

    void setIsClipMode(bool isClipMode) { m_clip_mode = isClipMode; }
    bool isClipMode() { return m_clip_mode; }

    void startClip() { if (isSelected()) m_clip_mode = true; }
    void endClip(DrawingBoard &board);

    void rotate(float angle, DrawingBoard &board);
    void scale(float factor, DrawingBoard &board);

private:
    QPoint m_clipStart, m_clipEnd;
    int m_selectRange = 10; // 5px
    bool m_select_mode = false;
    bool m_clip_mode = false;
    bool m_hasClipBox = false;
    QRect m_selectBox;
    QRect m_clipBox;

    QList<QList<QPoint>> m_polygons;

    enum { SHAPE_POLYGON, SHAPE_NONE } current_shape = SHAPE_NONE;
    QList<QPoint> m_points;
    QList<QPoint> m_translate_points;

    QPoint m_center_point;

    bool isDragPointMode = false;
    int dragPointIndex = 0;
};

#endif // POLYGONINSTRUMENT_H
