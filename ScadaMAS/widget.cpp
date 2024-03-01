#include "widget.h"
#include "mygraphicsscene.h"
#include "mainmenu.h"

#include <QApplication>
#include <QList>
#include <QScreen>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("ScadaMAS");
    QList<QScreen*> monitors = QGuiApplication::screens();
    if(!monitors.empty())
    {
        const QSize sizeWindow = monitors[0]->availableSize();
        this->setGeometry(0, 0, sizeWindow.width(), sizeWindow.height());
    }
    MyGraphicsScene* pScene = new MyGraphicsScene(QRectF(-100, -100, 640, 480));
    pView = new MyGraphicsView(pScene);
    MainMenu* pMenu = new MainMenu(pScene);
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pMenu);
    pvbxLayout->addWidget(pView);
    this->setLayout(pvbxLayout);
}
