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

    bool userMode() const;
    void setUserMode(bool mode);
    MyGraphicsScene* myScene();

public slots:
    void slotCreateRect();

private:
    bool isUserMode = false;
};

#endif // MYGRAPHICSSCENE_H
