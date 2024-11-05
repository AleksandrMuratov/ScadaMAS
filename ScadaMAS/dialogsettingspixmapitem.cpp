#include "dialogsettingspixmapitem.h"
#include "doublerangevalidator.h"
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

    QHBoxLayout* Frame = new QHBoxLayout();
    QLabel* frameOn = new QLabel("Рамка", this);


    QString color_background = "background-color: ";

    //Настройка цвета рамки
    QHBoxLayout* settings_color_frame = new QHBoxLayout();
    QLabel* label_color_frame = new QLabel("Цвет рамки", this);
    QPushButton* settings_color_frame_button = new QPushButton(this);
    settings_color_frame_button->setObjectName("ColorFrameButton");
    settings_color_frame_button->setStyleSheet(color_background + settings_.penColor.name() + ";");
    settings_color_frame->addWidget(label_color_frame);
    settings_color_frame->addWidget(settings_color_frame_button);
    QObject::connect(settings_color_frame_button, &QPushButton::clicked, this, &dialogSettingsPixmapItem::dialogSettingsColorFrame);
    QObject::connect(this, &dialogSettingsPixmapItem::setNewColorFrame, settings_color_frame_button, &QPushButton::setStyleSheet);

    // Настройка толщины рамки
    QHBoxLayout* settings_width_frame = new QHBoxLayout();
    QLabel* label_width_frame = new QLabel("Толщина рамки", this);
    QLineEdit* editWidthFrame = new QLineEdit(this);
    editWidthFrame->setObjectName("editWidthFrame");
    editWidthFrame->setValidator(new DoubleRangeValidator(0.0, 10.0, 1, this));
    editWidthFrame->setText(QString::number(settings_.widthPen, 'f', 1).replace('.', ','));
    settings_width_frame->addWidget(label_width_frame);
    settings_width_frame->addWidget(editWidthFrame);

    all_settings->addLayout(settings_color_frame);
    all_settings->addLayout(settings_width_frame);

    QDialogButtonBox* btn_box = new QDialogButtonBox(this);
    btn_box->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(btn_box, &QDialogButtonBox::accepted, this, &QDialog::accept);
    QObject::connect(btn_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
    QFormLayout* layout = new QFormLayout();
    layout->addRow(all_settings);
    layout->addWidget(btn_box);
    this->setLayout(layout);
}

QColor dialogSettingsPixmapItem::GetNewColorFrame() const
{
    return settings_.penColor;
}

qreal dialogSettingsPixmapItem::GetNewWidthFrame() const
{
    QLineEdit* editWidthFrame = this->findChild<QLineEdit*>("editWidthFrame");
    return editWidthFrame->text().replace(',', '.').toDouble();
}

bool dialogSettingsPixmapItem::FrameOn() const
{
    return settings_.frame;
}

void dialogSettingsPixmapItem::dialogSettingsColorFrame()
{
    QColor color = QColorDialog::getColor(settings_.penColor, this);
    if(color.isValid()){
        settings_.penColor = color;
        QString color_background = "background-color: ";
        color_background += settings_.penColor.name();
        color_background += ";";
        emit setNewColorFrame(color_background);
    }
}

}
