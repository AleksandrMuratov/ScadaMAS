#include "mygraphicsscene.h"
#include "mygraphicsrectitem.h"
#include "mypushbutton.h"

#include <QtWidgets>

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

MyGraphicsScene::MyGraphicsScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{}

void MyGraphicsScene::slotCreateRect()
{
    QPen pen(Qt::black);
    pen.setWidth(2);
    QBrush brush(Qt::green);
    MyGraphicsRectItem* rect = new MyGraphicsRectItem(QRectF(0, 0, 120, 80));
    rect->setPen(pen);
    rect->setBrush(brush);
    this->addItem(rect);
    rect->setPos(300, 300);
    QCursor cur(Qt::OpenHandCursor);
    rect->setCursor(cur);
}

void MyGraphicsScene::slotCreatePushButton()
{
    MyPushButton* button = new MyPushButton();
    button->setProxyWidget(this->addWidget(button));
}
