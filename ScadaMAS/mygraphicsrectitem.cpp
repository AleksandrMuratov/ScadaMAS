#include "mygraphicsrectitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <QPainter>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

MyGraphicsRectItem::MyGraphicsRectItem(QGraphicsItem* parent)
    : QObject()
    , QGraphicsRectItem(parent)
{
    this->setDefaultSettings();
}

MyGraphicsRectItem::MyGraphicsRectItem(const QRectF &rect, QGraphicsItem *parent)
    : QObject()
    , QGraphicsRectItem(rect, parent)
{
    this->setDefaultSettings();
}

void MyGraphicsRectItem::setDefaultSettings()
{
    this->setAcceptHoverEvents(true);
    this->setPen(settings.pen);
    this->setBrush(settings.color);
}

void MyGraphicsRectItem::setColor(QColor color)
{
    settings.color = color;
}

void MyGraphicsRectItem::setColorPressMouse(QColor color)
{
    settings.colorPressMouse = color;
}

void MyGraphicsRectItem::setText(const QString& txt)
{
    settings.text = txt;
}

MyGraphicsScene* MyGraphicsRectItem::getScene() const
{
    return dynamic_cast<MyGraphicsScene*>(this->scene());
}

bool MyGraphicsRectItem::isUserMode() const
{
    auto scene = this->getScene();
    return scene && scene->userMode();
}

void MyGraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
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
}

void MyGraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
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

void MyGraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
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
    this->setBrush(QBrush(settings.colorPressMouse));
}

void MyGraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!this->isUserMode())
    {
        if(!dataPressMouse.edges)
        {
            this->setCursor(QCursor(Qt::OpenHandCursor));
        }
        dataPressMouse.edges = Edges::NO;
    }
    this->setBrush(QBrush(settings.color));
    Q_UNUSED(event);
}

void MyGraphicsRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget)
{
    painter->setPen(this->pen());
    painter->setBrush(this->brush());
    painter->drawRoundedRect(this->rect(), 20.0, 15.0);
    painter->setFont(settings.font);
    painter->drawText(this->rect(), settings.alignFlag, settings.text);
}

int MyGraphicsRectItem::cursorOnFrame(QPointF p) const
{
    int edges = 0;
    qreal widthFrame = 10;
    QRectF rect = this->rect();
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

void MyGraphicsRectItem::resizeFrame(int edges, QPointF point)
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
    else if(edges & Edges::LEFT)
    {
        this->resizeFrameLeft(point);
    }
    else if(edges & Edges::RIGHT)
    {
        this->resizeFrameRight(point);
    }
    else if(edges & Edges::TOP)
    {
        this->resizeFrameTop(point);
    }
    else if(edges & Edges::BOTTOM)
    {
        this->resizeFrameDown(point);
    }
}

void MyGraphicsRectItem::setPosAndSize(qreal x, qreal y, qreal w, qreal h)
{
    if(w > minW && h > minH)
    {
        this->setPos(x, y);
        this->setRect(0, 0, w, h);
    }
}

void MyGraphicsRectItem::resizeFrameLeftTop(QPointF point)
{
    QPointF delta = this->scenePos() - point;
    QRectF rect = this->rect();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setPosAndSize(point.x(), point.y(), w, h);
}

void MyGraphicsRectItem::resizeFrameRightTop(QPointF point)
{
    QPointF rightTopAngle;
    QPointF curPos = this->scenePos();
    QRectF rect = this->rect();
    rightTopAngle.rx() = curPos.x() + rect.width();
    rightTopAngle.ry() = curPos.y();
    QPointF delta;
    delta.ry() = rightTopAngle.y() - point.y();
    delta.rx() = point.x() - rightTopAngle.x();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setPosAndSize(this->x(), point.y(), w, h);
}

void MyGraphicsRectItem::resizeFrameLeftDown(QPointF point)
{
    QPointF leftDownAngle;
    QPointF curPos = this->scenePos();
    QRectF rect = this->rect();
    leftDownAngle.rx() = curPos.x();
    leftDownAngle.ry() = curPos.y() + rect.height();
    QPointF delta;
    delta.rx() = leftDownAngle.x() - point.x();
    delta.ry() = point.y() - leftDownAngle.y();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setPosAndSize(point.x(), this->y(), w, h);
}
void MyGraphicsRectItem::resizeFrameRightDown(QPointF point)
{
    QPointF rightDownAngle;
    QPointF curPos = this->scenePos();
    QRectF rect = this->rect();
    rightDownAngle.rx() = curPos.x() + rect.width();
    rightDownAngle.ry() = curPos.y() + rect.height();
    QPointF delta;
    delta.rx() = point.x() - rightDownAngle.x();
    delta.ry() = point.y() - rightDownAngle.y();
    qreal w = rect.width() + delta.x();
    qreal h = rect.height() + delta.y();
    this->setPosAndSize(this->x(), this->y(), w, h);
}
void MyGraphicsRectItem::resizeFrameTop(QPointF point)
{
    qreal deltaY = this->scenePos().y() - point.y();
    QRectF rect = this->rect();
    qreal w = rect.width();
    qreal h = rect.height() + deltaY;
    this->setPosAndSize(this->x(), point.y(), w, h);
}
void MyGraphicsRectItem::resizeFrameLeft(QPointF point)
{
    qreal deltaX = this->scenePos().x() - point.x();
    QRectF rect = this->rect();
    qreal w = rect.width() + deltaX;
    qreal h = rect.height();
    this->setPosAndSize(point.x(), this->y(), w, h);
}
void MyGraphicsRectItem::resizeFrameRight(QPointF point)
{
    QRectF rect = this->rect();
    qreal deltaX = point.x() - (this->scenePos().x() + rect.width());
    qreal w = rect.width() + deltaX;
    qreal h = rect.height();
    this->setPosAndSize(this->x(), this->y(), w, h);
}
void MyGraphicsRectItem::resizeFrameDown(QPointF point)
{
    QRectF rect = this->rect();
    qreal deltaY = point.y() - (this->scenePos().y() + rect.height());
    qreal w = rect.width();
    qreal h = rect.height() + deltaY;
    this->setPosAndSize(this->x(), this->y(), w, h);
}

void MyGraphicsRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent* event){
    createContextMenu();
    context_menu.exec(event->screenPos());
}

void MyGraphicsRectItem::removeSelf()
{
    this->scene()->removeItem(this);
}

void MyGraphicsRectItem::openSettings()
{
    QDialog dlg;
    dlg.setWindowTitle(name_item);
    QLineEdit* edit_text = new QLineEdit(&dlg);
    edit_text->setText(settings.text);
    QDialogButtonBox* btn_box = new QDialogButtonBox(&dlg);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(btn_box, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(btn_box, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    QFormLayout* layout = new QFormLayout();
    layout->addRow(QString("Текст:"), edit_text);
    layout->addWidget(btn_box);
    dlg.setLayout(layout);
    if(dlg.exec() == QDialog::Accepted)
    {
        settings.text = edit_text->text();
    }
}

void MyGraphicsRectItem::createContextMenu()
{
    if(!context_menu_is_created){
        QAction* openSettings = context_menu.addAction("Настройки");
        QAction* removeAction = context_menu.addAction("Удалить");
        QObject::connect(removeAction, &QAction::triggered, this, &MyGraphicsRectItem::removeSelf);
        QObject::connect(openSettings, &QAction::triggered, this, &MyGraphicsRectItem::openSettings);
    }
    context_menu_is_created = true;
}
