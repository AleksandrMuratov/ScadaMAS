#include "mygraphicsrectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPainter>

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
    this->setAcceptHoverEvents(true);
}

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QGraphicsRectItem(rect, parent)
{
    this->setAcceptHoverEvents(true);
}

void MyGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    switch (cursorOnFrame(event->pos())) {
    case IntersectionWithFrame::LEFT_TOP:
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case IntersectionWithFrame::TOP:
        this->setCursor(QCursor(Qt::SizeVerCursor));
        break;
    case IntersectionWithFrame::RIGHT_TOP:
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case IntersectionWithFrame::LEFT:
        this->setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case IntersectionWithFrame::RIGHT:
        this->setCursor(QCursor(Qt::SizeHorCursor));
        break;
    case IntersectionWithFrame::LEFT_DOWN:
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
        break;
    case IntersectionWithFrame::RIGHT_DOWN:
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
        break;
    case IntersectionWithFrame::DOWN:
        this->setCursor(QCursor(Qt::SizeVerCursor));
        break;
    default:
        this->setCursor(QCursor(Qt::OpenHandCursor));
        break;
    }
}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if((dataPressMouse.mb & Qt::LeftButton) && dataPressMouse.intersectionWithFrame == IntersectionWithFrame::NO)
    {
        this->setPos(mapToScene(event->pos() - dataPressMouse.dPoint));
    }
    else
    {
        this->resizeFrame(dataPressMouse.intersectionWithFrame, mapToScene(event->pos()));
    }
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dataPressMouse.mb = event->button();
    dataPressMouse.dPoint = event->pos();
    dataPressMouse.intersectionWithFrame = cursorOnFrame(dataPressMouse.dPoint);
    if((dataPressMouse.mb & Qt::LeftButton) && dataPressMouse.intersectionWithFrame == IntersectionWithFrame::NO)
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    Q_UNUSED(event);
}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(dataPressMouse.intersectionWithFrame == IntersectionWithFrame::NO)
    {
        this->setCursor(QCursor(Qt::OpenHandCursor));
    }
    Q_UNUSED(event);
}

void MyGraphicsRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget)
{
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawRect(this->rect());
}

MyGraphicsRectItem::IntersectionWithFrame MyGraphicsRectItem::cursorOnFrame(QPointF p) const
{
    qreal widthFrame = 6;
    QRectF rect = this->boundingRect();
    if(p.x() < widthFrame && p.y() < widthFrame)
    {
        return IntersectionWithFrame::LEFT_TOP;
    }
    else if(p.x() < rect.width() - widthFrame && p.y() < widthFrame)
    {
        return IntersectionWithFrame::TOP;
    }
    else if(p.y() < widthFrame)
    {
        return IntersectionWithFrame::RIGHT_TOP;
    }
    else if(p.x() < widthFrame && p.y() < rect.height() - widthFrame)
    {
        return IntersectionWithFrame::LEFT;
    }
    else if(p.x() < widthFrame)
    {
        return IntersectionWithFrame::LEFT_DOWN;
    }
    else if(p.x() < rect.width() - widthFrame && p.y() >= rect.height() - widthFrame)
    {
        return IntersectionWithFrame::DOWN;
    }
    else if(p.x() >= rect.width() - widthFrame && p.y() < rect.height() - widthFrame)
    {
        return IntersectionWithFrame::RIGHT;
    }
    else if(p.x() >= rect.width() - widthFrame && p.y() >= rect.height() - widthFrame)
    {
        return IntersectionWithFrame::RIGHT_DOWN;
    }
    return IntersectionWithFrame::NO;
}

void MyGraphicsRectItem::resizeFrame(MyGraphicsRectItem::IntersectionWithFrame intersection, QPointF point)
{
    switch (intersection) {
    case IntersectionWithFrame::LEFT_TOP:
        this->resizeFrameLeftTop(point);
        break;
    case IntersectionWithFrame::TOP:
        this->resizeFrameTop(point);
        break;
    case IntersectionWithFrame::RIGHT_TOP:
        this->resizeFrameRightTop(point);
        break;
    case IntersectionWithFrame::LEFT:
        this->resizeFrameLeft(point);
        break;
    case IntersectionWithFrame::RIGHT:
        this->resizeFrameRight(point);
        break;
    case IntersectionWithFrame::LEFT_DOWN:
        this->resizeFrameLeftDown(point);
        break;
    case IntersectionWithFrame::RIGHT_DOWN:
        this->resizeFrameRightDown(point);
        break;
    case IntersectionWithFrame::DOWN:
        this->resizeFrameDown(point);
        break;
    }
}
void MyGraphicsRectItem::resizeFrameLeftTop(QPointF point)
{
    QPointF delta = this->scenePos() - point;
    QRectF rect = this->rect();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setRect(point.x(), point.y(), w, h);
}
void MyGraphicsRectItem::resizeFrameRightTop(QPointF point)
{
    QPointF rightAngle;
    QPointF curPos = this->scenePos();
    QRectF rect = this->rect();
    rightAngle.rx() = curPos.x() + rect.width();
    rightAngle.ry() = curPos.y();
    QPointF delta;
    delta.ry() = curPos.y() - rightAngle.y();
    delta.rx() = rightAngle.x() - curPos.x();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setRect(curPos.x(), point.y(), w, h);
}
void MyGraphicsRectItem::resizeFrameLeftDown(QPointF point)
{

}
void MyGraphicsRectItem::resizeFrameRightDown(QPointF point)
{

}
void MyGraphicsRectItem::resizeFrameTop(QPointF point)
{

}
void MyGraphicsRectItem::resizeFrameLeft(QPointF point)
{

}
void MyGraphicsRectItem::resizeFrameRight(QPointF point)
{

}
void MyGraphicsRectItem::resizeFrameDown(QPointF point)
{

}
