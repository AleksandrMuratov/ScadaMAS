#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget* parent)
    : QPushButton(parent)
{
    this->setGeometry(600, 600, 100, 80);
}

MyPushButton::MyPushButton(const QString& text, QWidget* parent)
    : QPushButton(text, parent)
{}

MyPushButton::MyPushButton(const QIcon& icon, const QString& text, QWidget* parent)
    : QPushButton(icon, text, parent)
{}

void MyPushButton::setProxyWidget(QGraphicsProxyWidget* pwgt)
{
    proxyWidget = pwgt;
}

void MyPushButton::setPos(qreal x, qreal y)
{
    if(proxyWidget)
    {
        proxyWidget->setPos(x, y);
    }
}
