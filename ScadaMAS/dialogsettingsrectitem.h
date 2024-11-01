#ifndef DIALOGSETTINGSRECTITEM_H
#define DIALOGSETTINGSRECTITEM_H

#include <QDialog>
#include <QPen>

namespace dialog_rect{

struct Settings{
    QString text;
    QFont font;
    QColor backGroundColor;
    QColor pressBackGroundColor;
    QColor penColor;
    qreal widthPen;
    qreal xRadius;
    qreal yRadius;
};

class dialogSettingsRectItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsRectItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QFont getNewFont() const;
    QColor getNewBackGroundColor() const;
    QColor getNewPressBackGroundColor() const;
    QColor getNewPenColor() const;

public slots:
    void settingsFont();
    void settingsColor();
    void settingsPressColor();
    void settingsPenColor();

signals:
    void setNewBackGroundColor(QString color);
    void setNewPressBackGroundColor(QString color);
    void setNewPenColor(QString color);

private:
    Settings settings_;
};

} //namespace dialog_rect



#endif // DIALOGSETTINGSRECTITEM_H
