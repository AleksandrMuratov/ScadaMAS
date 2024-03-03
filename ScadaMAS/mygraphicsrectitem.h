#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QGraphicsRectItem>

class MyGraphicsRectItem : public QGraphicsRectItem
{
public:
    MyGraphicsRectItem(QGraphicsItem* parent = nullptr);

    MyGraphicsRectItem(const QRectF& rect, QGraphicsItem* parent = nullptr);

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget) override;

private:
    enum class IntersectionWithFrame
    {
        NO,
        LEFT_TOP,
        RIGHT_TOP,
        LEFT_DOWN,
        RIGHT_DOWN,
        TOP,
        DOWN,
        LEFT,
        RIGHT
    };

    IntersectionWithFrame cursorOnFrame(QPointF p) const;

    void resizeFrame(IntersectionWithFrame intersection, QPointF point);
    void resizeFrameLeftTop(QPointF point);
    void resizeFrameRightTop(QPointF point);
    void resizeFrameLeftDown(QPointF point);
    void resizeFrameRightDown(QPointF point);
    void resizeFrameTop(QPointF point);
    void resizeFrameLeft(QPointF point);
    void resizeFrameRight(QPointF point);
    void resizeFrameDown(QPointF point);

    struct DataPressMouse
    {
        Qt::MouseButton mb;
        QPointF dPoint;
        IntersectionWithFrame intersectionWithFrame;
    };
    DataPressMouse dataPressMouse;
};

#endif // MYGRAPHICSRECTITEM_H
