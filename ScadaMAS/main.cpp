#include "widget.h"
#include "mainmenu.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget wgt;
    wgt.show();
    return a.exec();
    // https://yandex.ru/images/search?img_url=https%3A%2F%2Fimg2018.cnblogs.com%2Fblog%2F1502586%2F201908%2F1502586-20190829080556488-734962628.png&lr=11269&pos=6&rpt=simage&source=serp&stype=image&text=qt%20%D0%B8%D0%B5%D1%80%D0%B0%D1%80%D1%85%D0%B8%D1%8F%20%D0%BA%D0%BB%D0%B0%D1%81%D1%81%D0%BE%D0%B2
}
