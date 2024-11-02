#ifndef DIALOGSETTINGSPIXMAPITEM_H
#define DIALOGSETTINGSPIXMAPITEM_H

#include <QDialog>
#include <QPen>

namespace dialog_pixmap{

struct Settings{
    bool frame = false;
    qreal widthPen = 1.0;
    QColor penColor = Qt::black;
};

class dialogSettingsPixmapItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsPixmapItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPen GetPen() const;
    bool FrameOn() const;

private:
    Settings settings_;
};

} // namespace dialog_pixmap



#endif // DIALOGSETTINGSPIXMAPITEM_H
