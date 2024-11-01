#include "dialogsettingspixmapitem.h"

namespace dialog_pixmap {

dialogSettingsPixmapItem::dialogSettingsPixmapItem(Settings settings, QWidget* parent, Qt::WindowFlags f):
    QDialog(parent, f),
    frame_(settings.frame),
    pen_(QPen(settings.color_pen))
{
    pen_.setWidth(settings.width_pen);
}

}
