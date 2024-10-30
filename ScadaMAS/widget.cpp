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
    QSize sizeWindow;
    if(!monitors.empty())
    {
        sizeWindow = monitors[0]->availableSize();
        this->setGeometry(0, 0, sizeWindow.width(), sizeWindow.height());
    }
    MyGraphicsScene* pScene = new MyGraphicsScene(QRectF(0, 0, sizeWindow.width(), sizeWindow.height()));
    pView = new MyGraphicsView(pScene, this);
    MainMenu* pMenu = new MainMenu(pScene);
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pMenu);
    pvbxLayout->addWidget(pView);
    this->setLayout(pvbxLayout);
}
