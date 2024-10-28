#ifndef DIALOGSETTINGSMENURECTITEM_H
#define DIALOGSETTINGSMENURECTITEM_H

#include <QDialog>

class dialogSettingsRectItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsRectItem(const QFont& font, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QFont getNewFont() const;

public slots:
    void settingsFont();
private:
    QFont new_font_;
};

#endif // DIALOGSETTINGSMENURECTITEM_H
