#ifndef MYGRAPHICSRECTITEM_H
#define MYGRAPHICSRECTITEM_H

#include "mygraphicsscene.h"

#include <QObject>
#include <QGraphicsRectItem>
#include <QtWidgets>
#include <QGraphicsTextItem>


class MyGraphicsRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    MyGraphicsRectItem(QGraphicsItem* parent = nullptr);

    MyGraphicsRectItem(const QRectF& rect, QGraphicsItem* parent = nullptr);

    void setColor(QColor color);
    void setColorPressMouse(QColor color);
    MyGraphicsScene* getScene() const;
    bool isUserMode() const;
    void setText(const QString& str);

public slots:
    void removeSelf();
    void openSettings();
    // void settingsFont();

protected:

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem * option, QWidget* widget) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override;


private:
    void setDefaultSettings();

    enum Edges
    {
        NO = 0,
        TOP = 1,
        LEFT = 2,
        RIGHT = 4,
        BOTTOM = 8
    };

    int cursorOnFrame(QPointF p) const;

    void resizeFrame(int edges, QPointF point);
    void resizeFrameLeftTop(QPointF point);
    void resizeFrameRightTop(QPointF point);
    void resizeFrameLeftDown(QPointF point);
    void resizeFrameRightDown(QPointF point);
    void resizeFrameTop(QPointF point);
    void resizeFrameLeft(QPointF point);
    void resizeFrameRight(QPointF point);
    void resizeFrameDown(QPointF point);
    void setPosForScene(QPointF pos);
    void setPosAndSize(qreal x, qreal y, qreal w, qreal h);
    void createContextMenu();

    struct DataPressMouse
    {
        Qt::MouseButton mb;
        QPointF dPoint;
        int edges;
    };
    struct Settings
    {
        QColor color = Qt::green;
        QColor colorPressMouse = Qt::darkGreen;
        QPen pen = []()
        {
            QPen pen = QPen(Qt::black);
            pen.setWidth(2);
            return pen;
        }();
        QFont font = QFont("Times New Roman", 25, QFont::Normal);
        QString text;
        Qt::AlignmentFlag alignFlag = Qt::AlignCenter;
        qreal xRadius = 20.0;
        qreal yRadius = 15.0;
    };
    QMenu context_menu;
    bool context_menu_is_created = false;
    QString name_item;
    Settings settings;
    DataPressMouse dataPressMouse;
    qreal minW = 10;
    qreal minH = 10;

};

#endif // MYGRAPHICSRECTITEM_H
