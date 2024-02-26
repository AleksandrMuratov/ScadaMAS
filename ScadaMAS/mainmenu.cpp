#include "mainmenu.h"

MainMenu::MainMenu(QWidget* parent):
    QMenuBar(parent)
{
    menu = this->addMenu("Меню");
    menuAction = menu->menuAction();
    createObject = menu->addAction("Создать");
    //createObject->toggled();
}
