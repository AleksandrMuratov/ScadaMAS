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
    if(dataPressMouse.mb & Qt::LeftButton)
    {
        this->setPos(mapToScene(event->pos()) - dataPressMouse.dPoint);
    }
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dataPressMouse.mb = event->button();
    dataPressMouse.dPoint = event->buttonDownPos(dataPressMouse.mb);
    if(dataPressMouse.mb & Qt::LeftButton)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    Q_UNUSED(event);
}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->setCursor(QCursor(Qt::OpenHandCursor));
    Q_UNUSED(event);
}
