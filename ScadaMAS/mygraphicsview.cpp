#include "mygraphicsview.h"

MyGraphicsView::MyGraphicsView(QWidget* parrent)
    : QGraphicsView(parrent)
{}

MyGraphicsView::MyGraphicsView(QGraphicsScene *scene, QWidget *parrent)
    : QGraphicsView(scene, parrent)
{}

void MyGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    QGraphicsScene* pScene = this->scene();
    if(pScene)
    {
        fitInView(pScene->sceneRect(), Qt::KeepAspectRatio);
    }
}
