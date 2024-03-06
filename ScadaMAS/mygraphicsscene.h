#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QObject>

class MyGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MyGraphicsScene(QObject *parent = nullptr);
    explicit MyGraphicsScene(const QRectF& sceneRect, QObject* parent = nullptr);

public slots:
    void slotCreateRect();
    void slotCreatePushButton();

private:

};

#endif // MYGRAPHICSSCENE_H
