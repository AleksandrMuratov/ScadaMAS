#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget wgt;
    wgt.show();
    // QList<QScreen*> monitors = QGuiApplication::screens();
    // QSize sizeWindow;
    // if(!monitors.empty())
    // {
    //     sizeWindow = monitors[0]->availableSize();
    // }
    // MyGraphicsScene Scene(QRectF(0, 0, sizeWindow.width(), sizeWindow.height()));
    // MyGraphicsView View(&Scene);
    // MainMenu* pMenu = new MainMenu(&Scene);
    // Scene.addWidget(pMenu);
    // View.show();
    return a.exec();
}
