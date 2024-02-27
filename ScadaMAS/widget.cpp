#include "widget.h"
#include "mygraphicsscene.h"
#include "mainmenu.h"

#include <QApplication>
#include <QList>
#include <QScreen>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

Widget::Widget(QWidget *parent)
    : QWidget{parent}
{
    this->setWindowTitle("ScadaMAS");
    QList<QScreen*> monitors = QGuiApplication::screens();
    if(!monitors.empty())
    {
        const QSize sizeWindow = monitors[0]->availableSize();
        this->setGeometry(0, 0, sizeWindow.width(), sizeWindow.height());
    }
    QGraphicsView view(this);
    MyGraphicsScene* scene = new MyGraphicsScene(&view);
    QGraphicsRectItem* rect = scene->addRect(QRectF(-30, -30, 120, 80), QPen(Qt::black), QBrush(Qt::green));
    rect->setFlags(QGraphicsItem::ItemIsMovable);
    MainMenu* menu = new MainMenu(scene, this);
}
