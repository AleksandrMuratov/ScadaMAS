#ifndef WIDGET_H
#define WIDGET_H

#include "mygraphicsview.h"

#include <QWidget>
#include <QGraphicsView>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

public slots:


private:
    MyGraphicsView* pView;
};

#endif // WIDGET_H
