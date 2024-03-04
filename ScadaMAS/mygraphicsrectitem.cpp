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
    int edges = cursorOnFrame(mapToScene(event->pos()));
    if(((edges & Edges::LEFT) && (edges & Edges::TOP))
        || ((edges & Edges::RIGHT) && (edges & Edges::BOTTOM)))
    {
        this->setCursor(QCursor(Qt::SizeFDiagCursor));
    }
    else if(((edges & Edges::RIGHT) && (edges & Edges::TOP))
               || ((edges & Edges::LEFT) && (edges & Edges::BOTTOM)))
    {
        this->setCursor(QCursor(Qt::SizeBDiagCursor));
    }
    else if((edges & Edges::LEFT) || (edges & Edges::RIGHT))
    {
        this->setCursor(QCursor(Qt::SizeHorCursor));
    }
    else if((edges & Edges::TOP) || (edges & Edges::BOTTOM))
    {
        this->setCursor(QCursor(Qt::SizeVerCursor));
    }
    else
    {
        this->setCursor(QCursor(Qt::OpenHandCursor));
    }
}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if((dataPressMouse.mb & Qt::LeftButton) && (!dataPressMouse.edges))
    {
        this->setPos(mapToScene(event->pos() - dataPressMouse.dPoint));
    }
    else
    {
        this->resizeFrame(static_cast<Edges>(dataPressMouse.edges), mapToScene(event->pos()));
    }
}

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    dataPressMouse.mb = event->button();
    dataPressMouse.dPoint = event->pos();
    dataPressMouse.edges = cursorOnFrame(mapToScene(dataPressMouse.dPoint));
    if((dataPressMouse.mb & Qt::LeftButton) && (!dataPressMouse.edges))
    {
        this->setCursor(QCursor(Qt::ClosedHandCursor));
    }
    Q_UNUSED(event);
}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!dataPressMouse.edges)
    {
        this->setCursor(QCursor(Qt::OpenHandCursor));
    }
    dataPressMouse.edges = Edges::NO;
    Q_UNUSED(event);
}

void MyGraphicsRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget)
{
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawRect(this->rect());
}

int MyGraphicsRectItem::cursorOnFrame(QPointF p) const
{
    int edges = 0;
    qreal widthFrame = 10;
    QRectF rect = this->rect();
    auto ppprect = this->boundingRect();

    if(QRectF(this->x(), this->y(), widthFrame, rect.height()).contains(p))
    {
        edges |= Edges::LEFT;
    }
    if(QRectF(this->x() + rect.width() - widthFrame, this->y(), widthFrame, rect.height()).contains(p))
    {
        edges |= Edges::RIGHT;
    }
    if(QRectF(this->x(), this->y(), rect.width(), widthFrame).contains(p))
    {
        edges |= Edges::TOP;
    }
    if(QRectF(this->x(), this->y() + rect.height() - widthFrame, rect.width(), widthFrame).contains(p))
    {
        edges |= Edges::BOTTOM;
    }
    return edges;
}

void MyGraphicsRectItem::resizeFrame(Edges edges, QPointF point)
{
    // switch (intersection) {
    // case IntersectionWithFrame::LEFT_TOP:
    //     this->resizeFrameLeftTop(point);
    //     break;
    // case IntersectionWithFrame::TOP:
    //     this->resizeFrameTop(point);
    //     break;
    // case IntersectionWithFrame::RIGHT_TOP:
    //     this->resizeFrameRightTop(point);
    //     break;
    // case IntersectionWithFrame::LEFT:
    //     this->resizeFrameLeft(point);
    //     break;
    // case IntersectionWithFrame::RIGHT:
    //     this->resizeFrameRight(point);
    //     break;
    // case IntersectionWithFrame::LEFT_DOWN:
    //     this->resizeFrameLeftDown(point);
    //     break;
    // case IntersectionWithFrame::RIGHT_DOWN:
    //     this->resizeFrameRightDown(point);
    //     break;
    // case IntersectionWithFrame::DOWN:
    //     this->resizeFrameDown(point);
    //     break;
    // }
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
