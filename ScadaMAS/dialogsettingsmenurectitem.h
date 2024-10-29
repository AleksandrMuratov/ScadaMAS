#ifndef DIALOGSETTINGSMENURECTITEM_H
#define DIALOGSETTINGSMENURECTITEM_H

#include <QDialog>

namespace dialog_rect{

struct Settings{
    QFont font;
    QColor backGroundColor;
    QColor pressBackGroundColor;
};

class dialogSettingsRectItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsRectItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QFont getNewFont() const;
    QColor getNewBackGroundColor() const;
    QColor getNewPressBackGroundColor() const;

public slots:
    void settingsFont();
    void settingsColor();
    void settingsPressColor();

signals:
    void setNewBackGroundColor(QString color);
    void setNewPressBackGroundColor(QString color);

private:
    QFont new_font_;
    QColor new_backGroundColor_;
    QColor new_press_backGroundColor_;
};

} //namespace dialog_rect



#endif // DIALOGSETTINGSMENURECTITEM_H
