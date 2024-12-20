#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QWidget>

class LayerManager : public QWidget
{
    Q_OBJECT
public:
    explicit LayerManager(QWidget *parent = nullptr);

signals:
};

#endif // LAYERMANAGER_H
