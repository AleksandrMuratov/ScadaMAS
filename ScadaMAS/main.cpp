#include "LayerManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LayerManager w;
    w.show();
    return a.exec();
}
