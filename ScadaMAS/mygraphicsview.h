#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    MyGraphicsView(QWidget* parrent = nullptr);
    MyGraphicsView(QGraphicsScene* scene, QWidget* parrent = nullptr);

protected:
    void wheelEvent(QWheelEvent* event) override;

protected slots:
    void resizeEvent(QResizeEvent* event);
};

#endif // MYGRAPHICSVIEW_H
