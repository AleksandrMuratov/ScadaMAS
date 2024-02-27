#include "mygraphicsscene.h"

#include <QtWidgets>


MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void MyGraphicsScene::slotCreateButton()
{
    QGraphicsRectItem* rect = this->addRect(QRectF(-30, -30, 120, 80), QPen(Qt::black), QBrush(Qt::green));
    rect->setFlags(QGraphicsItem::ItemIsMovable);
}
