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
    MyGraphicsRectItem* rect = new MyGraphicsRectItem(QRectF(0, 0, 120, 80));
    rect->setPen(pen);
    rect->setBrush(brush);
    this->addItem(rect);
    QCursor cur(Qt::OpenHandCursor);
    rect->setCursor(cur);
}
