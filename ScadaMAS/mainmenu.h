#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMenuBar>

class MainMenu : public QMenuBar
{
    Q_OBJECT
public:
    MainMenu(QWidget* parrent = nullptr);

private:
    QMenu* menu = nullptr;
    QAction* menuAction = nullptr;
    QAction* createObject = nullptr;
};

#endif // MAINMENU_H
