#include "dialogsettingspixmapitem.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

namespace dialog_pixmap {

dialogSettingsPixmapItem::dialogSettingsPixmapItem(Settings settings, QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f),
    settings_(settings)
{
    QVBoxLayout* all_settings = new QVBoxLayout();

    //Настройка цвета рамки
    QHBoxLayout* settings_color_frame = new QHBoxLayout();
    QLabel* label_color_frame = new QLabel("Цвет рамки", this);
    QPushButton* settings_color_frame_button = new QPushButton(this);
    settings_color_frame_button->setStyleSheet(color_background + settings_.penColor.name() + ";");
    settings_color_frame->addWidget(label_color_frame);
    settings_color_frame->addWidget(settings_color_frame_button);
    QObject::connect(settings_color_frame_button, &QPushButton::clicked, this, dialog_rect::dialogSettingsRectItem::settingsPenColor);
    QObject::connect(this, &dialog_rect::dialogSettingsRectItem::setNewPenColor, settings_color_frame_button, &QPushButton::setStyleSheet);

}

}
