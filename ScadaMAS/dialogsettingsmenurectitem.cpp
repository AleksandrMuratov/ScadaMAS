#include "dialogsettingsmenurectitem.h"
#include <QFontDialog>

dialogSettingsRectItem::dialogSettingsRectItem(const QFont& font, QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f),
    new_font_(font)
{}

QFont dialogSettingsRectItem::getNewFont() const
{
    return new_font_;
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
