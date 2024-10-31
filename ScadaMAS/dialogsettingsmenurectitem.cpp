#include "dialogsettingsmenurectitem.h"
#include <QFontDialog>
#include <QColorDialog>

namespace dialog_rect {

dialogSettingsRectItem::dialogSettingsRectItem(Settings settings, QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f),
    new_font_(settings.font),
    new_backGroundColor_(settings.backGroundColor),
    new_press_backGroundColor_(settings.pressBackGroundColor)
{}

QFont dialogSettingsRectItem::getNewFont() const
{
    return new_font_;
}

QColor dialogSettingsRectItem::getNewBackGroundColor() const
{
    return new_backGroundColor_;
}

QColor dialogSettingsRectItem::getNewPressBackGroundColor() const
{
    return new_press_backGroundColor_;
}

void dialogSettingsRectItem::settingsFont()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, new_font_, this, QString::fromUtf8("Выберите шрифт"));
    if(ok)
    {
        new_font_ = font;
    }
}

void dialogSettingsRectItem::settingsColor()
{
    QColor color = QColorDialog::getColor(new_backGroundColor_, this);
    if(color.isValid()){
        new_backGroundColor_ = color;
        QString color_background = "background-color: ";
        color_background += new_backGroundColor_.name();
        color_background += ";";
        emit setNewBackGroundColor(color_background);
    }
}

void dialogSettingsRectItem::settingsPressColor()
{
    QColor color = QColorDialog::getColor(new_backGroundColor_, this);
    if(color.isValid()){
        new_press_backGroundColor_ = color;
        QString color_background = "background-color: ";
        color_background += new_press_backGroundColor_.name();
        color_background += ";";
        emit setNewPressBackGroundColor(color_background);
    }
}

} // namespace dialog_rect


