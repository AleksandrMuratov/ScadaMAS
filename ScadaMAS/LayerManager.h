#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QWidget>

class LayerManager : public QWidget
{
    Q_OBJECT

public:
    LayerManager(QWidget *parent = nullptr);
    ~LayerManager();
};
#endif // LAYERMANAGER_H
