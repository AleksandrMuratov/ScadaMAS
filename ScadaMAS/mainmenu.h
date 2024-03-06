#ifndef MAINMENU_H
#define MAINMENU_H
#include "mygraphicsscene.h"

#include <QMenuBar>

class MainMenu : public QMenuBar
{
    Q_OBJECT
public:
    MainMenu(MyGraphicsScene* scene, QWidget* parrent = nullptr);

private:
    QMenu* menu = nullptr;
    QAction* menuAction = nullptr;
    QMenu* createObject = nullptr;
    QAction* createRect = nullptr;
    QAction* createPushButton = nullptr;
};

#endif // MAINMENU_H
