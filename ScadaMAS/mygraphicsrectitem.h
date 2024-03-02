#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include <QGraphicsRectItem>

class MyGraphicsRectItem : public QGraphicsRectItem
{
public:
    MyGraphicsRectItem(QGraphicsItem* parent = nullptr);

    MyGraphicsRectItem(const QRectF& rect, QGraphicsItem* parent = nullptr);

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

private:
    struct DataPressMouse
    {
        Qt::MouseButton mb;
        QPointF dPoint;
    };
    DataPressMouse dataPressMouse;
};

#endif // MYGRAPHICSRECTITEM_H
