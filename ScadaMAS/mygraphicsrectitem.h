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
    //void paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget) override;

private:
    enum Edges
    {
        NO = 0,
        TOP = 1,
        LEFT = 2,
        RIGHT = 4,
        BOTTOM = 8
    };

    int cursorOnFrame(QPointF p) const;

    void resizeFrame(int edges, QPointF point);
    void resizeFrameLeftTop(QPointF point);
    void resizeFrameRightTop(QPointF point);
    void resizeFrameLeftDown(QPointF point);
    void resizeFrameRightDown(QPointF point);
    void resizeFrameTop(QPointF point);
    void resizeFrameLeft(QPointF point);
    void resizeFrameRight(QPointF point);
    void resizeFrameDown(QPointF point);
    void setPosAndSize(qreal x, qreal y, qreal w, qreal h);

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

#endif // MYGRAPHICSRECTITEM_H
