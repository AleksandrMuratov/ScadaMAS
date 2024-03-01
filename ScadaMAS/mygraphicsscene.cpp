#include "mygraphicsscene.h"

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
    QGraphicsRectItem* rect = this->addRect(QRectF(-30, -30, 120, 80), pen, QBrush(Qt::green));
    rect->setFlags(QGraphicsItem::ItemIsMovable|QGraphicsItem::ItemIsSelectable);
}
