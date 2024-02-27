#include "mainmenu.h"

MainMenu::MainMenu(MyGraphicsScene* scene, QWidget* parent):
    QMenuBar(parent)
{
    menu = this->addMenu("Меню");
    menuAction = menu->menuAction();
    createObject = menu->addMenu("Cоздать");
    createButton = createObject->addAction("Кнопка");
    if(scene)
    {
        QObject::connect(createButton, &QAction::triggered, scene, &MyGraphicsScene::slotCreateButton);
    }
}
