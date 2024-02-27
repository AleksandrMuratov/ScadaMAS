#include "widget.h"
#include "mainmenu.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget wgt;
    wgt.show();
    return a.exec();
}
