#ifndef DIALOGSETTINGSPIXMAPITEM_H
#define DIALOGSETTINGSPIXMAPITEM_H

#include <QDialog>
#include <QPen>

namespace dialog_pixmap{

struct Settings{
    bool frame = false;
    qreal widthPen = 5.0;
    QColor penColor = Qt::black;
};

class dialogSettingsPixmapItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsPixmapItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QColor GetNewColorFrame() const;
    qreal GetNewWidthFrame() const;
    bool FrameOn() const;

public slots:
    void dialogSettingsColorFrame();

signals:
    void setNewColorFrame(QString color);

private:
    Settings settings_;
};

} // namespace dialog_pixmap



#endif // DIALOGSETTINGSPIXMAPITEM_H
