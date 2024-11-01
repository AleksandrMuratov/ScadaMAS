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

QRectF MyGraphicsPixmapItem::getRectForPen() const
{
    qreal width_pen = settings.pen.widthF();
    QRectF rect = this->boundingRect();
    rect.setX(rect.x() + width_pen/2);
    rect.setY(rect.y() + width_pen/2);
    rect.setWidth(rect.width() - width_pen/2);
    rect.setHeight(rect.height() - width_pen/2);
    return rect;
}

void MyGraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);
    painter->setPen(settings.pen);
    QColor gr = Qt::green;
    gr.setAlphaF(0.0);
    painter->setBrush(QBrush(gr));
    painter->drawRect(this->getRectForPen());
}

QPointF MyGraphicsPixmapItem::getPointIntersectionLeftDiagonal(QPointF point) const
{
    QPointF m1 = this->scenePos();
    QRectF rect = this->getRect();
    QPointF m2(m1.x() + rect.width(), m1.y() + rect.height());
    qreal k = (m2.y() - m1.y())/(m2.x() - m1.x());
    qreal b1 = (m1.y()*m2.x() - m1.x()*m2.y())/(m2.x()-m1.x());
    qreal b2 = point.y() + point.x()/k;
    QPointF res;
    res.rx() = (b2 - b1)/(k + 1/k);
    res.ry() = k*res.x() + b1;
    return res;
}

QPointF MyGraphicsPixmapItem::getPointIntersectionRightDiagonal(QPointF point) const
{
    QPointF m1 = this->scenePos();
    QRectF rect = this->getRect();
    m1.rx() = m1.x() + rect.width();
    QPointF m2(m1.x() - rect.width(), m1.y() + rect.height());
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
            this->resizeFrame(dataPressMouse.edges, mapToScene(event->pos()));
        }
    }
}

void MyGraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    dataPressMouse.mb = event->button();
    dataPressMouse.dPoint = event->pos();
    dataPressMouse.edges = cursorOnAngle(mapToScene(dataPressMouse.dPoint));
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
        int edges = cursorOnAngle(mapToScene(event->pos()));
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

int MyGraphicsPixmapItem::cursorOnAngle(QPointF p) const
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
        this->resizeFrameLeftTop(this->getPointIntersectionLeftDiagonal(point));
    }
    else if((edges & Edges::RIGHT) && (edges & Edges::BOTTOM))
    {
        this->resizeFrameRightDown(this->getPointIntersectionLeftDiagonal(point));
    }
    else if((edges & Edges::RIGHT) && (edges & Edges::TOP))
    {
        this->resizeFrameRightTop(this->getPointIntersectionRightDiagonal(point));
    }
    else if((edges & Edges::LEFT) && (edges & Edges::BOTTOM))
    {
        this->resizeFrameLeftDown(this->getPointIntersectionRightDiagonal(point));
    }
}

void MyGraphicsPixmapItem::resizeFrameLeftTop(QPointF point)
{
    QPointF delta = this->scenePos() - point;
    QRectF rect = this->getRect();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    QPointF rightDownAngle;
    QPointF curLeftTopAngle = this->scenePos();
    rightDownAngle.rx() = curLeftTopAngle.x() + rect.width();
    rightDownAngle.ry() = curLeftTopAngle.y() + rect.height();
    QPointF newLeftTopAngle;
    newLeftTopAngle.rx() = rightDownAngle.x() - w;
    newLeftTopAngle.ry() = rightDownAngle.y() - h;
    this->setPosAndSize(w, h, newLeftTopAngle);
}

void MyGraphicsPixmapItem::resizeFrameRightTop(QPointF point)
{
    QRectF rect = this->getRect();
    QPointF curRightTopAngle = this->scenePos();
    curRightTopAngle.rx() = curRightTopAngle.x() + rect.width();
    QPointF delta;
    delta.rx() = point.x() - curRightTopAngle.x();
    delta.ry() = curRightTopAngle.y() - point.y();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    QPointF curLeftTopAngle = this->scenePos();
    QPointF curLeftDownAngle = curLeftTopAngle;
    curLeftDownAngle.ry() = curLeftTopAngle.y() + rect.height();
    QPointF newLeftTopAngle;
    newLeftTopAngle.rx() = curLeftTopAngle.x();
    newLeftTopAngle.ry() = curLeftDownAngle.y() - h;
    this->setPosAndSize(w, h, newLeftTopAngle);
}

void MyGraphicsPixmapItem::resizeFrameLeftDown(QPointF point)
{
    QRectF rect = this->getRect();
    QPointF curLeftDownAngle = this->scenePos();
    curLeftDownAngle.ry() = curLeftDownAngle.y() + rect.height();
    QPointF delta;
    delta.rx() = curLeftDownAngle.x() - point.x();
    delta.ry() = point.y() - curLeftDownAngle.y();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    QPointF newLeftTopAngle;
    QPointF curRightTopAngle = this->scenePos();
    curRightTopAngle.rx() = curRightTopAngle.x() + rect.width();
    newLeftTopAngle.rx() = curRightTopAngle.x() - w;
    newLeftTopAngle.ry() = curRightTopAngle.y();
    this->setPosAndSize(w, h, newLeftTopAngle);
}

void MyGraphicsPixmapItem::resizeFrameRightDown(QPointF point)
{
    QRectF rect = this->getRect();
    QPointF curRightDownAngle = this->scenePos();
    curRightDownAngle.rx() = curRightDownAngle.x() + rect.width();
    curRightDownAngle.ry() = curRightDownAngle.y() + rect.height();
    QPointF delta;
    delta.rx() = point.x() - curRightDownAngle.x();
    delta.ry() = point.y() - curRightDownAngle.y();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    QPointF newLeftTopAngle = this->scenePos();
    this->setPosAndSize(w, h, newLeftTopAngle);
}

void MyGraphicsPixmapItem::setPosAndSize(qreal w, qreal h, QPointF newLeftTopAngle)
{
    if(w > minW && h > minH)
    {
        this->setScale(h/this->boundingRect().height());
        this->setPos(newLeftTopAngle);
    }
}

void MyGraphicsPixmapItem::removeSelf()
{
    this->scene()->removeItem(this);
}

void MyGraphicsPixmapItem::createContextMenu()
{
    if(!context_menu_is_created){
        QAction* openSettings = context_menu.addAction("Настройки");
        QAction* removeAction = context_menu.addAction("Удалить");
        QObject::connect(removeAction, &QAction::triggered, this, &MyGraphicsPixmapItem::removeSelf);
    }
    context_menu_is_created = true;
}

void MyGraphicsPixmapItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
{
    createContextMenu();
    context_menu.exec(event->screenPos());
}
