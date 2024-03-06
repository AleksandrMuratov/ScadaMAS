#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QGraphicsProxyWidget>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QWidget* parent = nullptr);
    MyPushButton(const QString& text, QWidget* parent = nullptr);
    MyPushButton(const QIcon& icon, const QString& text, QWidget* parent = nullptr);

    void setProxyWidget(QGraphicsProxyWidget* pwgt);
    void setPos(qreal x, qreal y);

private:
    QGraphicsProxyWidget* proxyWidget = nullptr;
};

#endif // MYPUSHBUTTON_H
