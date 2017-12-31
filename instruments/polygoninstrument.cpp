#include "polygoninstrument.h"
#include "../drawingboard.h"
#include "core/painter.h"
#include <QPainter>
#include <QLine>
#include <QDebug>

QPoint getCenterPoint(QList<QPoint> &points);
QPoint do_rotate(QPoint p, float angle, QPoint center);
QPoint do_scale(QPoint p, float factor, QPoint center);
QList<QPoint> bezierCurve(QList<QPoint> points);

PolygonInstrument::PolygonInstrument(QObject *parent) :
    AbstractInstrument(parent)
{

}


void PolygonInstrument::mousePressEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::LeftButton && isClipMode()) {
        board.setIsInPaint(false);
        m_clipStart = m_clipEnd = event->pos();
        m_hasClipBox = true;
//        mImageCopy = QImage(*board.getVectorImage());
    }
    else if (event->button() == Qt::LeftButton && isSelected()) {
        for (int i = 0; i < m_points.size(); i++) {
            QPoint p = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            float rx = p.x() - event->pos().x();
            float ry = p.y() - event->pos().y();
            if (sqrt(rx*rx + ry*ry) < m_selectRange) {
                isDragPointMode = true;
                dragPointIndex = i;
                break;
            }
        }
    }
}

void PolygonInstrument::mouseMoveEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(board.isInPaint()) {
        mEndPoint = event->pos();
        if (m_points.size() > 2) {
            float rx = m_points[0].x() - event->pos().x();
            float ry = m_points[0].y() - event->pos().y();
            if (sqrt(rx*rx + ry*ry) < m_selectRange) {
                mEndPoint = m_points[0];
            }
        }
        draw(board);
    }
    else if (isClipMode() && event->buttons() | Qt::LeftButton) {
        m_clipEnd = event->pos();
        draw(board);
    }
    else if (isDragPointMode) {
        QPoint new_pos = do_rotate(do_scale(event->pos(), 1.0f / board.getScaleFactor(), m_center_point), -board.getRotateAngle(), m_center_point);
        m_points[dragPointIndex] = new_pos;
        if (dragPointIndex == 0) {
            m_points.last() = new_pos;
        } else if (dragPointIndex == m_points.size() - 1) {
            m_points.first() = new_pos;
        }
        draw(board);
    }
}

void PolygonInstrument::mouseReleaseEvent(QMouseEvent *event, DrawingBoard &board)
{
    if(event->button() == Qt::RightButton) {
        board.setIsInPaint(false);
        setIsSelected(false);
        m_points.clear();
        board.setVectorImage(mImageCopy);
        board.update();
    }
    else if (event->button() == Qt::LeftButton) {
        if (isClipMode()) {
            setIsClipMode(false);
            m_hasClipBox = true;
        }
        else if (isDragPointMode) {
            isDragPointMode = false;
        }
        else if (isSelected() && !m_selectBox.contains(event->pos())) {
            for(int i = 0; i < m_points.size(); i++) {
                m_points[i] = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            }
            board.setIsInPaint(false);
            setIsSelected(false);
            if (current_shape == SHAPE_POLYGON) {
                board.addPolygon(m_points);
                m_polygons.append(m_points);
            } else if (current_shape == SHAPE_CURVE3 || current_shape == SHAPE_CURVE4) {
                board.addCurve(m_points);
                m_curves.append(m_points);
            }

            m_points.clear();
            draw(board);
            board.resetScaleAndRotate();
        }
        else if (!board.isInPaint()) {
//            qDebug() << "in paint";
            setIsSelected(false);
            isDragPointMode = false;
            m_points.clear();
            mStartPoint = mEndPoint = event->pos();
            board.setIsInPaint(true);
            m_hasClipBox = false;
//            mImageCopy = QImage(*board.getVectorImage());
            m_points.append(mEndPoint);
            draw(board);
        }
        else if(board.isInPaint()) {
            if (current_shape == SHAPE_CURVE3) {
                mStartPoint = mEndPoint = event->pos();
                if (m_points.size() == 2) {
                    setIsSelected(true);
                    board.setIsInPaint(false);
                }
                m_points.append(mEndPoint);
                m_center_point = getCenterPoint(m_points);
                draw(board);
            }
            else if (current_shape == SHAPE_CURVE4) {
                mStartPoint = mEndPoint = event->pos();
                if (m_points.size() == 3) {
                    setIsSelected(true);
                    board.setIsInPaint(false);
                }
                m_points.append(mEndPoint);
                m_center_point = getCenterPoint(m_points);
                draw(board);
            }
            else {
                mStartPoint = mEndPoint = event->pos();

                if (m_points.size() > 2) {
                    float rx = m_points[0].x() - event->pos().x();
                    float ry = m_points[0].y() - event->pos().y();
                    if (sqrt(rx*rx + ry*ry) < m_selectRange) {
                        mStartPoint = mEndPoint = m_points[0];
                        setIsSelected(true);
                        board.setIsInPaint(false);
                    }
                }

                m_points.append(mEndPoint);
                m_center_point = getCenterPoint(m_points);
                draw(board);
            }

    //        board.setIsInPaint(false);
        }
    }
}

void PolygonInstrument::draw(DrawingBoard &board)
{
    QImage *vector_image = new QImage(board.getVectorImage()->width(), board.getVectorImage()->height(), QImage::Format_ARGB32);
    QPainter bg_painter(vector_image);
    bg_painter.fillRect(0, 0, vector_image->width(), vector_image->height(), Qt::white);
    bg_painter.end();

    CorePainter::Painter mypainter(vector_image);

    // draw existing shapes
    for (int i = 0; i < m_polygons.size(); i++) {
        for (int j = 1; j < m_polygons[i].size(); j++) {
            mypainter.drawLine(m_polygons[i][j - 1], m_polygons[i][j]);
        }
    }
    for (int i = 0; i < m_curves.size(); i++) {
        QList<QPoint> points = bezierCurve(m_curves[i]);
        for(int j = 1; j < points.size(); j++) {
            mypainter.drawLine(points[j - 1], points[j]);
        }
    }

    // draw current drawing shape
    if (current_shape == SHAPE_POLYGON) {
        for(int i = 1; i < m_points.size(); i++) {
            QPoint p1 = do_rotate(do_scale(m_points[i - 1], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            QPoint p2 = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            mypainter.drawLine(p1, p2);
        }
        for(int i = 0; i < m_points.size(); i++) {
            QPoint p = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            mypainter.drawCircle(p.x(), p.y(), m_selectRange, Qt::blue);
        }

        if(mStartPoint != mEndPoint)
        {
            mypainter.drawLine(mStartPoint, mEndPoint);
        }

        if(mStartPoint == mEndPoint)
        {
            mypainter.drawPoint(mStartPoint);
        }
    }
    else if (current_shape == SHAPE_CURVE3 || current_shape == SHAPE_CURVE4) {
        QList<QPoint> points = m_points;
        if (board.isInPaint()) {
            points.append(mEndPoint);
        }
        points = bezierCurve(points);
        for(int i = 1; i < points.size(); i++) {
            QPoint p1 = do_rotate(do_scale(points[i - 1], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            QPoint p2 = do_rotate(do_scale(points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            mypainter.drawLine(p1, p2);
        }

        for(int i = 0; i < m_points.size(); i++) {
            QPoint p = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
            mypainter.drawCircle(p.x(), p.y(), m_selectRange, Qt::blue);
        }
    } else {

    }

    if (isSelected()) {
        QPainter painter(vector_image);

        // draw center point
        painter.setBrush(QBrush(Qt::green));
        painter.drawEllipse(m_center_point, 3, 3);
        painter.setBrush(QBrush());

        if (m_points.size() < 1) {
            qDebug() << "m_points < 1";
        }
        else {
            int left, bottom, right, top;
            QPoint p = do_rotate(do_scale(m_points[0], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);

            left = p.x();
            bottom = p.y();
            right = p.x();
            top = p.y();
            for (int i = 0; i < m_points.size(); i++) {
                QPoint p = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);

                if (p.x() < left) {
                    left = p.x();
                }
                if (p.x() > right) {
                    right = p.x();
                }
                if (p.y() < bottom) {
                    bottom = p.y();
                }
                if (p.y() > top) {
                    top = p.y();
                }
            }
            m_selectBox = QRect(left - 20, bottom - 20, right - left + 40, top - bottom + 40);
            painter.setPen(QPen(Qt::blue, 1, Qt::DashLine));
            painter.drawRect(m_selectBox);
        }
    }

    if (isClipMode() && m_hasClipBox) {
        QPainter painter(vector_image);
        painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
        painter.drawRect(QRect(m_clipStart, m_clipEnd));
    }

    board.setVectorImage(*vector_image);

    board.update();
}

bool isClockWise(QList<QPoint> &points) {
    int res = 0;
    for (int i = 0; i < points.size(); i++) {
        res += (points[(i + 1) % points.size()].x() - points[i].x()) * (points[(i + 1) % points.size()].y() + points[i].y());
    }
    return res < 0;
}

QPoint intersect(QLine line1, QLine line2) {
    QPoint p;
    int x1 = line1.x1(), y1 = line1.y1(), x2 = line1.x2(), y2= line1.y2();
    int x3 = line2.x1(), y3 = line2.y1(), x4 = line2.x2(), y4= line2.y2();
    int num = (x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    p.setX(num / den);
    num = (x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4);
    den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    p.setY(num / den);
    return p;
}

QList<QPoint> clip(QList<QPoint> polygon, QRect clipping_box) {
    QList<QPoint> clip_polygon;
    // clip left edge
    for (int i = 0; i < polygon.size(); i++) {
        QPoint p1 = polygon[i], p2 = polygon[(i + 1) % polygon.size()];
        bool p1_inside = p1.x() > clipping_box.left();
        bool p2_inside = p2.x() > clipping_box.left();
        if (p1_inside && p2_inside) {
            clip_polygon.append(p2);
        }
        else if (p1_inside && !p2_inside) {
            QLine clip_line(clipping_box.bottomLeft(), clipping_box.topLeft());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
        }
        else if (!p1_inside && p2_inside) {
            QLine clip_line(clipping_box.bottomLeft(), clipping_box.topLeft());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
            clip_polygon.append(p2);
        }
        else {

        }
    }
    polygon = clip_polygon;
    clip_polygon.clear();
    // clip right edge
    for (int i = 0; i < polygon.size(); i++) {
        QPoint p1 = polygon[i], p2 = polygon[(i + 1) % polygon.size()];
        bool p1_inside = p1.x() < clipping_box.right();
        bool p2_inside = p2.x() < clipping_box.right();
        if (p1_inside && p2_inside) {
            clip_polygon.append(p2);
        }
        else if (p1_inside && !p2_inside) {
            QLine clip_line(clipping_box.bottomRight(), clipping_box.topRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
        }
        else if (!p1_inside && p2_inside) {
            QLine clip_line(clipping_box.bottomRight(), clipping_box.topRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
            clip_polygon.append(p2);
        }
        else {

        }
    }
    polygon = clip_polygon;
    clip_polygon.clear();
    // clip top edge
    for (int i = 0; i < polygon.size(); i++) {
        QPoint p1 = polygon[i], p2 = polygon[(i + 1) % polygon.size()];
        bool p1_inside = p1.y() > clipping_box.top();
        bool p2_inside = p2.y() > clipping_box.top();
        if (p1_inside && p2_inside) {
            clip_polygon.append(p2);
        }
        else if (p1_inside && !p2_inside) {
            QLine clip_line(clipping_box.topLeft(), clipping_box.topRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
        }
        else if (!p1_inside && p2_inside) {
            QLine clip_line(clipping_box.topLeft(), clipping_box.topRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
            clip_polygon.append(p2);
        }
        else {

        }
    }
    polygon = clip_polygon;
    clip_polygon.clear();
    // clip bottom edge
    for (int i = 0; i < polygon.size(); i++) {
        QPoint p1 = polygon[i], p2 = polygon[(i + 1) % polygon.size()];
        bool p1_inside = p1.y() < clipping_box.bottom();
        bool p2_inside = p2.y() < clipping_box.bottom();
        if (p1_inside && p2_inside) {
            clip_polygon.append(p2);
        }
        else if (p1_inside && !p2_inside) {
            QLine clip_line(clipping_box.bottomLeft(), clipping_box.bottomRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
        }
        else if (!p1_inside && p2_inside) {
            QLine clip_line(clipping_box.bottomLeft(), clipping_box.bottomRight());
            clip_polygon.append(intersect(QLine(p1, p2), clip_line));
            clip_polygon.append(p2);
        }
        else {

        }
    }
    clip_polygon.append(clip_polygon[0]);
    return clip_polygon;
}

void PolygonInstrument::endClip(DrawingBoard &board) {
    if (m_hasClipBox) {
        qDebug() << "clip";
        for (int i = 0; i < m_points.size(); i++) {
            m_points[i] = do_rotate(do_scale(m_points[i], board.getScaleFactor(), m_center_point), board.getRotateAngle(), m_center_point);
        }
        m_points = clip(m_points, QRect(m_clipStart, m_clipEnd));
        for (int i = 0; i < m_points.size(); i++) {
            m_points[i] = do_rotate(do_scale(m_points[i], 1.0f / board.getScaleFactor(), m_center_point), -board.getRotateAngle(), m_center_point);
        }
        draw(board);
        setIsSelected(true);
    }
}


QPoint getCenterPoint(QList<QPoint> &points) {
    QPoint p;
    int x = 0, y = 0;
    for (int i = 0; i < points.size(); i++) {
        x += points[i].x();
        y += points[i].y();
    }
    p.setX(x / points.size());
    p.setY(y / points.size());
    return p;
}


QPoint do_rotate(QPoint p, float angle, QPoint center) {
    float s = sin(angle * 3.1415926f / 180.0f);
    float c = cos(angle * 3.1415926f / 180.0f);

    p.setX(p.x() - center.x());
    p.setY(p.y() - center.y());

    float xnew = p.x() * c - p.y() * s;
    float ynew = p.x() * s + p.y() * c;

    p.setX(xnew + center.x());
    p.setY(ynew + center.y());

    return p;
}

QPoint do_scale(QPoint p, float factor, QPoint center) {
    p.setX(p.x() - center.x());
    p.setY(p.y() - center.y());

    float xnew = p.x() * factor;
    float ynew = p.y() * factor;

    p.setX(xnew + center.x());
    p.setY(ynew + center.y());

    return p;
}

void PolygonInstrument::rotate(float angle, DrawingBoard &board) {
    draw(board);
}

void PolygonInstrument::scale(float factor, DrawingBoard &board) {
    draw(board);
}

void PolygonInstrument::setCurveMode(int curve_points) {
    if (curve_points == 3) {
        current_shape = SHAPE_CURVE3;
//        qDebug() << "1111 " << curve_points;
    } else if (curve_points == 4) {
        current_shape = SHAPE_CURVE4;
    } else {
        qDebug() << "curve mode unknown";
    }
}

QPoint getBezierPoint(QList<QPoint> points, float delta) {
    QList<QPoint> tmp = points;
    int i = points.size() - 1;
    while (i > 0) {
        for (int k = 0; k < i; k++)
            tmp[k] = tmp[k] + delta * (tmp[k+1] - tmp[k]);
        i--;
    }
    return tmp[0];
}

QList<QPoint> bezierCurve(QList<QPoint> points) {
    QList<QPoint> result;
    if (points.size() <= 2) {
         return points;
    }
    else {
        for (float i = 0 ; i < 1 ; i += 0.01 ){
            result.append(getBezierPoint(points, i));
        }
    }

    return result;
}
