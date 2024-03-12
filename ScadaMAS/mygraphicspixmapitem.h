#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include "mygraphicsscene.h"

#include <QGraphicsPixmapItem>

class MyGraphicsPixmapItem : public QGraphicsPixmapItem
{
public:
    MyGraphicsPixmapItem(QGraphicsItem* parent = nullptr);
    MyGraphicsPixmapItem(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    bool isUserMode() const;
    MyGraphicsScene* getScene() const;
    QRectF getRect() const;

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    void setDefaultSettings();
    int cursorOnAngle(QPointF p) const;
    void resizeFrame(int edges, QPointF point);
    void resizeFrameLeftTop(QPointF point);
    void resizeFrameRightTop(QPointF point);
    void resizeFrameLeftDown(QPointF point);
    void resizeFrameRightDown(QPointF point);
    QPointF getPointIntersectionLeftDiagonal(QPointF point) const;
    QPointF getPointIntersectionRightDiagonal(QPointF point) const;
    QPoint pointFromSceneToGlobal(QPointF point) const;

    enum Edges
    {
        NO = 0,
        TOP = 1,
        LEFT = 2,
        RIGHT = 4,
        BOTTOM = 8
    };

    struct DataPressMouse
    {
        Qt::MouseButton mb;
        QPointF dPoint;
        int edges;
    };

    DataPressMouse dataPressMouse;
    qreal minW = 1;
    qreal minH = 1;
};

#endif // MYGRAPHICSPIXMAPITEM_H
