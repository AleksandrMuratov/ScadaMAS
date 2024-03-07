#include "mainmenu.h"

MainMenu::MainMenu(MyGraphicsScene* scene, QWidget* parent):
    QMenuBar(parent)
{
    menu = this->addMenu("Меню");
    menuAction = menu->menuAction();
    createObject = menu->addMenu("Cоздать");
    createRect = createObject->addAction("Кнопка");
    if(scene)
    {
        QObject::connect(createRect, &QAction::triggered, scene, &MyGraphicsScene::slotCreateRect);
    }
}
