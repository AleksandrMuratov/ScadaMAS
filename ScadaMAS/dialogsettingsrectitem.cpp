#include "dialogsettingsrectitem.h"
#include "doublerangevalidator.h"
#include <QFontDialog>
#include <QColorDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>

namespace dialog_rect {

dialogSettingsRectItem::dialogSettingsRectItem(Settings settings, QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f),
    settings_(settings)
{
    QVBoxLayout* all_settings = new QVBoxLayout();

    //Настройка текста и шрифта
    QHBoxLayout* settings_text = new QHBoxLayout();
    QLabel* label_text = new QLabel("Текст", this);
    QLineEdit* edit_text = new QLineEdit(this);
    edit_text->setObjectName("text");
    edit_text->setText(settings_.text);
    QPushButton* settings_font = new QPushButton("Шрифт", this);
    QObject::connect(settings_font, &QPushButton::clicked, this, dialog_rect::dialogSettingsRectItem::settingsFont);
    settings_text->addWidget(label_text);
    settings_text->addWidget(edit_text);
    settings_text->addWidget(settings_font);

    QString color_background = "background-color: ";

    //Настройка фона
    QHBoxLayout* settings_color = new QHBoxLayout();
    QLabel* label_color = new QLabel("Цвет фона", this);
    QPushButton* settings_color_button = new QPushButton(this);
    settings_color_button->setStyleSheet(color_background + settings_.backGroundColor.name() + ";");
    settings_color->addWidget(label_color);
    settings_color->addWidget(settings_color_button);
    QObject::connect(settings_color_button, &QPushButton::clicked, this, dialog_rect::dialogSettingsRectItem::settingsColor);
    QObject::connect(this, &dialog_rect::dialogSettingsRectItem::setNewBackGroundColor, settings_color_button, &QPushButton::setStyleSheet);

    //Настройка фона при нажатии ЛКМ
    QHBoxLayout* settings_press_color = new QHBoxLayout();
    QLabel* label_press_color = new QLabel("Цвет фона при нажатии", this);
    QPushButton* settings_press_color_button = new QPushButton(this);
    settings_press_color_button->setStyleSheet(color_background + settings_.pressBackGroundColor.name() + ";");
    settings_press_color->addWidget(label_press_color);
    settings_press_color->addWidget(settings_press_color_button);
    QObject::connect(settings_press_color_button, &QPushButton::clicked, this, dialog_rect::dialogSettingsRectItem::settingsPressColor);
    QObject::connect(this, &dialog_rect::dialogSettingsRectItem::setNewPressBackGroundColor, settings_press_color_button, &QPushButton::setStyleSheet);

    //Настройка радиуса углов прямоугольника по оси X
    QHBoxLayout* settingsRadius = new QHBoxLayout();
    QLabel* label_x_radius = new QLabel("Радиус угла по X", this);
    QLineEdit* editXRadius = new QLineEdit(this);
    editXRadius->setObjectName("editXRadius");
    editXRadius->setValidator(new DoubleRangeValidator(0.0, std::numeric_limits<double>::max(), 1, this));
    editXRadius->setText(QString::number(settings_.xRadius, 'f', 1).replace('.', ','));
    settingsRadius->addWidget(label_x_radius);
    settingsRadius->addWidget(editXRadius);

    //Настройка радиуса углов прямоугольника по оси Y
    QLabel* label_y_radius = new QLabel("по Y", this);
    QLineEdit* editYRadius = new QLineEdit(this);
    editYRadius->setObjectName("editYRadius");
    //editYRadius->setValidator(new QDoubleValidator(this));
    editYRadius->setValidator(new DoubleRangeValidator(0.0, std::numeric_limits<double>::max(), 1, this));
    editYRadius->setText(QString::number(settings_.yRadius, 'f', 1).replace('.', ','));
    settingsRadius->addWidget(label_y_radius);
    settingsRadius->addWidget(editYRadius);

    //Настройка цвета рамки
    QHBoxLayout* settings_color_frame = new QHBoxLayout();
    QLabel* label_color_frame = new QLabel("Цвет рамки", this);
    QPushButton* settings_color_frame_button = new QPushButton(this);
    settings_color_frame_button->setStyleSheet(color_background + settings_.penColor.name() + ";");
    settings_color_frame->addWidget(label_color_frame);
    settings_color_frame->addWidget(settings_color_frame_button);
    QObject::connect(settings_color_frame_button, &QPushButton::clicked, this, dialog_rect::dialogSettingsRectItem::settingsPenColor);
    QObject::connect(this, &dialog_rect::dialogSettingsRectItem::setNewPenColor, settings_color_frame_button, &QPushButton::setStyleSheet);

    //Настройка толщины рамки
    QHBoxLayout* settings_width_frame = new QHBoxLayout();
    QLabel* label_width_frame = new QLabel("Толщина рамки", this);
    QLineEdit* editWidthFrame = new QLineEdit(this);
    editWidthFrame->setObjectName("editWidthFrame");
    editWidthFrame->setValidator(new DoubleRangeValidator(0.0, 10.0, 1, this));
    editWidthFrame->setText(QString::number(settings_.widthPen, 'f', 1).replace('.', ','));
    settings_width_frame->addWidget(label_width_frame);
    settings_width_frame->addWidget(editWidthFrame);


    all_settings->addLayout(settings_text);
    all_settings->addLayout(settings_color);
    all_settings->addLayout(settings_press_color);
    all_settings->addLayout(settingsRadius);
    all_settings->addLayout(settings_color_frame);
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

QFont dialogSettingsRectItem::getNewFont() const
{
    return settings_.font;
}

QColor dialogSettingsRectItem::getNewBackGroundColor() const
{
    return settings_.backGroundColor;
}

QColor dialogSettingsRectItem::getNewPressBackGroundColor() const
{
    return settings_.pressBackGroundColor;
}

QColor dialogSettingsRectItem::getNewPenColor() const
{
    return settings_.penColor;
}

void dialogSettingsRectItem::settingsFont()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, settings_.font, this, QString::fromUtf8("Выберите шрифт"));
    if(ok)
    {
        settings_.font = font;
    }
}

void dialogSettingsRectItem::settingsColor()
{
    QColor color = QColorDialog::getColor(settings_.backGroundColor, this);
    if(color.isValid()){
        settings_.backGroundColor = color;
        QString color_background = "background-color: ";
        color_background += settings_.backGroundColor.name();
        color_background += ";";
        emit setNewBackGroundColor(color_background);
    }
}

void dialogSettingsRectItem::settingsPressColor()
{
    QColor color = QColorDialog::getColor(settings_.pressBackGroundColor, this);
    if(color.isValid()){
        settings_.pressBackGroundColor = color;
        QString color_background = "background-color: ";
        color_background += settings_.pressBackGroundColor.name();
        color_background += ";";
        emit setNewPressBackGroundColor(color_background);
    }
}

void dialogSettingsRectItem::settingsPenColor()
{
    QColor color = QColorDialog::getColor(settings_.penColor, this);
    if(color.isValid()){
        settings_.penColor = color;
        QString color_background = "background-color: ";
        color_background += settings_.penColor.name();
        color_background += ";";
        emit setNewPenColor(color_background);
    }
}

} // namespace dialog_rect


