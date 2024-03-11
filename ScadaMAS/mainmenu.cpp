#include "mainmenu.h"

MainMenu::MainMenu(MyGraphicsScene* scene, QWidget* parent):
    QMenuBar(parent)
{
    menu = this->addMenu("Меню");
    menuAction = menu->menuAction();
    createObject = menu->addMenu("Cоздать");
    createRect = createObject->addAction("Кнопка");
    createDynamicPicture = createObject->addAction("Динамическая картинка");
    if(scene)
    {
        QObject::connect(createRect, &QAction::triggered, scene, &MyGraphicsScene::slotCreateRect);
        QObject::connect(createDynamicPicture, &QAction::triggered, scene, &MyGraphicsScene::slotCreateDynamicPicture);
    }
}
