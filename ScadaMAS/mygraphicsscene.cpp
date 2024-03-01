#include "mygraphicsscene.h"
#include "mygraphicsrectitem.h"

#include <QtWidgets>

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

MyGraphicsScene::MyGraphicsScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{}

void MyGraphicsScene::slotCreateButton()
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::green);
    MyGraphicsRectItem* rect = new MyGraphicsRectItem(QRectF(-30, -30, 120, 80));
    rect->setPen(pen);
    rect->setBrush(brush);
    this->addItem(rect);
    //QGraphicsRectItem* rect = this->addRect(QRectF(-30, -30, 120, 80), pen, QBrush(Qt::green));
    //rect->setFlags(QGraphicsItem::ItemIsSelectable);
    QCursor cur(Qt::OpenHandCursor);
    rect->setCursor(cur);
}
