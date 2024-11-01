#ifndef DIALOGSETTINGSPIXMAPITEM_H
#define DIALOGSETTINGSPIXMAPITEM_H

#include <QDialog>
#include <QPen>

namespace dialog_pixmap{

struct Settings{
    bool frame = false;
    qreal width_pen = 0.0;
    QColor color_pen = Qt::black;
};

class dialogSettingsPixmapItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsPixmapItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QPen GetPen() const;
    bool FrameOn() const;

private:
    bool frame_;
    QPen pen_;
};

} // namespace dialog_pixmap



#endif // DIALOGSETTINGSPIXMAPITEM_H
