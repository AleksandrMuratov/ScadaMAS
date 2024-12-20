#ifndef DIALOGSETTINGSPIXMAPITEM_H
#define DIALOGSETTINGSPIXMAPITEM_H

#include <QDialog>
#include <QPen>

namespace dialog_pixmap{

struct Settings{
    bool frame = false;
    qreal widthPen = 5.0;
    QColor penColor = Qt::black;
    QString fileName;
};

class dialogSettingsPixmapItem : public QDialog
{
    Q_OBJECT
public:
    dialogSettingsPixmapItem(Settings settings, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    QColor GetNewColorFrame() const;
    qreal GetNewWidthFrame() const;
    const QString& GetNewPathToImage() const;
    bool FrameOn() const;

public slots:
    void dialogSettingsColorFrame();
    void dialogSelectFileImage();

signals:
    void setNewColorFrame(QString color);

private:
    Settings settings_;
};

} // namespace dialog_pixmap



#endif // DIALOGSETTINGSPIXMAPITEM_H
