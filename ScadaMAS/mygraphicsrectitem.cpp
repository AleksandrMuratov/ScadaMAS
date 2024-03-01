#include "mygraphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{}

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QPointF point = mapToScene(event->pos());
    this->setPos(point.x(), point.y());
}
