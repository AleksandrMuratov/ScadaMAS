#include "mygraphicsscene.h"
#include "mygraphicsrectitem.h"
#include "mygraphicspixmapitem.h"

#include <QtWidgets>
#include <QGraphicsTextItem>

MyGraphicsScene::MyGraphicsScene(QObject *parent)
    : QGraphicsScene{parent}
{}

MyGraphicsScene::MyGraphicsScene(const QRectF &sceneRect, QObject *parent)
    : QGraphicsScene(sceneRect, parent)
{}

void MyGraphicsScene::slotCreateRect()
{
    MyGraphicsRectItem* rect = new MyGraphicsRectItem(QRectF(0, 0, 120, 80));
    this->addItem(rect);
    rect->setPos(300, 300);
    QCursor cur(Qt::OpenHandCursor);
    rect->setCursor(cur);
}

void MyGraphicsScene::slotCreateDynamicPicture()
{
    MyGraphicsPixmapItem* pixmap = new MyGraphicsPixmapItem();
    this->addItem(pixmap);
}

bool MyGraphicsScene::userMode() const
{
    return isUserMode;
}
void MyGraphicsScene::setUserMode(bool mode)
{
    isUserMode = mode;
}
