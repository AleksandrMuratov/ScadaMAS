#include "widget.h"

#include <QApplication>
#include <QList>
#include <QScreen>

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
}
