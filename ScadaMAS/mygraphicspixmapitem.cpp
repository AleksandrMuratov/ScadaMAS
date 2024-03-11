#include "mygraphicspixmapitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QTransform>
#include <QGraphicsView>
#include <QGraphicsScene>

MyGraphicsPixmapItem::MyGraphicsPixmapItem(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{
    this->setDefaultSettings();
}

MyGraphicsPixmapItem::MyGraphicsPixmapItem(const QPixmap& pixmap, QGraphicsItem* parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    this->setDefaultSettings();
}

void MyGraphicsPixmapItem::setDefaultSettings()
{
    this->setAcceptHoverEvents(true);
    this->setPixmap(QPixmap("C:/picters/1.jpg"));
}

bool MyGraphicsPixmapItem::isUserMode() const
{
    auto scene = this->getScene();
    return scene && scene->userMode();
}

MyGraphicsScene* MyGraphicsPixmapItem::getScene() const
{
    return dynamic_cast<MyGraphicsScene*>(this->scene());
}

QRectF MyGraphicsPixmapItem::getRect() const
{
    QRectF rect = this->boundingRect();
    qreal sc = this->scale();
    rect.setHeight(rect.height()*sc);
    rect.setWidth(rect.width()*sc);
    return rect;
}

QPointF MyGraphicsPixmapItem::getPointIntersection(QPointF point) const
{
    QPointF m1 = this->scenePos();
    QRectF rect = this->boundingRect();
    QPointF m2(m1.x() + rect.width(), m1.y() + rect.height());
    qreal k = (m2.y() - m1.y())/(m2.x() - m1.x());
    qreal b1 = (m1.y()*m2.x() - m1.x()*m2.y())/(m2.x()-m1.x());
    qreal b2 = point.y() + point.x()/k;
    QPointF res;
    res.rx() = (b2 - b1)/(k + 1/k);
    res.ry() = k*res.x() + b1;
    return res;
}

QPoint MyGraphicsPixmapItem::pointFromSceneToGlobal(QPointF point) const
{
    QPoint res(0, 0);
    QGraphicsScene* scene = this->scene();
    QList<QGraphicsView*> views = scene->views();
    if(!views.empty())
    {
        QGraphicsView* view = views.front();
        QPoint pointView = view->mapFromScene(point);
        res = view->mapToGlobal(pointView);
    }
    return res;
}

void MyGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if(!this->isUserMode())
    {
        if((dataPressMouse.mb & Qt::LeftButton) && (!dataPressMouse.edges))
        {
            this->setPos(mapToScene(event->pos() - dataPressMouse.dPoint));
        }
        else
        {
            QPointF point = mapToScene(event->pos());
            QPointF pointIntersection = this->getPointIntersection(point);
            QPoint pointGlobal = this->pointFromSceneToGlobal(pointIntersection);
            this->resizeFrame(dataPressMouse.edges, pointIntersection);
            //QCursor::setPos(pointGlobal);
        }
    }
}

void MyGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    dataPressMouse.mb = event->button();
    dataPressMouse.dPoint = event->pos();
    dataPressMouse.edges = cursorOnFrame(mapToScene(dataPressMouse.dPoint));
    if(!this->isUserMode())
    {
        if((dataPressMouse.mb & Qt::LeftButton) && (!dataPressMouse.edges))
        {
            this->setCursor(QCursor(Qt::ClosedHandCursor));
        }
    }
}

void MyGraphicsPixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    if(!this->isUserMode())
    {
        if(!dataPressMouse.edges)
        {
            this->setCursor(QCursor(Qt::OpenHandCursor));
        }
        dataPressMouse.edges = Edges::NO;
    }

}

void MyGraphicsPixmapItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
    if(!this->isUserMode())
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
        else
        {
            this->setCursor(QCursor(Qt::OpenHandCursor));
        }
    }
}

int MyGraphicsPixmapItem::cursorOnFrame(QPointF p) const
{
    int edges = 0;
    qreal widthFrame = 5;
    QRectF rect = this->getRect();
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

void MyGraphicsPixmapItem::resizeFrame(int edges, QPointF point)
{
    if((edges & Edges::LEFT) && (edges & Edges::TOP))
    {
        this->resizeFrameLeftTop(point);
    }
    else if((edges & Edges::RIGHT) && (edges & Edges::BOTTOM))
    {
        this->resizeFrameRightDown(point);
    }
    else if((edges & Edges::RIGHT) && (edges & Edges::TOP))
    {
        this->resizeFrameRightTop(point);
    }
    else if((edges & Edges::LEFT) && (edges & Edges::BOTTOM))
    {
        this->resizeFrameLeftDown(point);
    }
}
void MyGraphicsPixmapItem::resizeFrameLeftTop(QPointF point)
{
    QPointF delta = this->scenePos() - point;
    QRectF rect = this->getRect();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setPosAndSize(point.x(), point.y(), w, h);
}
void MyGraphicsPixmapItem::resizeFrameRightTop(QPointF point)
{

}
void MyGraphicsPixmapItem::resizeFrameLeftDown(QPointF point)
{

}
void MyGraphicsPixmapItem::resizeFrameRightDown(QPointF point)
{

}
void MyGraphicsPixmapItem::setPosAndSize(qreal x, qreal y, qreal w, qreal h)
{
    QRectF rect = this->boundingRect();
    qreal sc = this->scale();
    rect.setHeight(rect.height()*sc);
    rect.setWidth(rect.width()*sc);
    // QTransform transform;
    // transform.scale(h/rect.height(), w/rect.width());
    // this->setTransform(transform);
    qreal delta_sc = 0.0;
    if(h/rect.height() > 1.1)
    {
        delta_sc = 0.1;
    }
    else if(h/rect.height() < 0.9)
    {
        delta_sc = -0.1;
    }
    if(h/rect.height() > 1.1 || h/rect.height() < 0.9)
    {

        this->setScale(this->scale() + delta_sc);
        this->setPos(x, y);
    }

    // QPixmap pixmap = this->pixmap();
    // qreal sc = h/rect.height();
    // this->setPixmap(pixmap.scaled(rect.height() * sc, rect.width() * sc));
    //this->setPos(x, y);
}
