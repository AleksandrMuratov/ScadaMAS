#include "mygraphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{}

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    this->setPos(mapToScene(event->pos()));
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::ClosedHandCursor));
    Q_UNUSED(event);
}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::OpenHandCursor));
    Q_UNUSED(event);
}
