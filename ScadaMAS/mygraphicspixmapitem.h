#ifndef MYGRAPHICSPIXMAPITEM_H
#define MYGRAPHICSPIXMAPITEM_H

#include "mygraphicsscene.h"

#include <QGraphicsPixmapItem>
#include <QMenu>

class MyGraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MyGraphicsPixmapItem(QGraphicsItem* parent = nullptr);
    MyGraphicsPixmapItem(const QPixmap& pixmap, QGraphicsItem* parent = nullptr);

    bool isUserMode() const;
    MyGraphicsScene* getScene() const;
    QRectF getRect() const;

public slots:
    void removeSelf();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;

private:
    void setDefaultSettings();
    int cursorOnAngle(QPointF p) const;
    void resizeFrame(int edges, QPointF point);
    void resizeFrameLeftTop(QPointF point);
    void resizeFrameRightTop(QPointF point);
    void resizeFrameLeftDown(QPointF point);
    void resizeFrameRightDown(QPointF point);
    QPointF getPointIntersectionLeftDiagonal(QPointF point) const;
    QPointF getPointIntersectionRightDiagonal(QPointF point) const;
    QPoint pointFromSceneToGlobal(QPointF point) const;
    void setPosAndSize(qreal w, qreal h, QPointF newLeftTopAngle);
    void setPosForScene(QPointF pos);
    void createContextMenu();

    enum Edges
    {
        NO = 0,
        TOP = 1,
        LEFT = 2,
        RIGHT = 4,
        BOTTOM = 8
    };

    struct DataPressMouse
    {
        Qt::MouseButton mb;
        QPointF dPoint;
        int edges;
    };

    QMenu context_menu;
    bool context_menu_is_created = false;
    DataPressMouse dataPressMouse;
    qreal minW = 10;
    qreal minH = 10;
};

#endif // MYGRAPHICSPIXMAPITEM_H
