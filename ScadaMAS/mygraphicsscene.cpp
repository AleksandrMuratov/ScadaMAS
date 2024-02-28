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
    QGraphicsRectItem* rect = this->addRect(QRectF(-30, -30, 120, 80), QPen(Qt::black), QBrush(Qt::green));
    rect->setFlags(QGraphicsItem::ItemIsMovable);
}
