#include "mygraphicsview.h"
#include <QWheelEvent>
#include <QApplication>

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

void MyGraphicsView::wheelEvent(QWheelEvent* event)
{
    if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
        // Если нажата клавиша CTRL, этот код выполнится
        auto delta = event->angleDelta().y();
        if(delta > 0){
            this->scale(1.1, 1.1);
        }
        else if(delta < 0){
            this->scale(1/1.1, 1/1.1);
        }
    }
}
