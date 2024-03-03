#include "mainwindow.h"

#include <QApplication> //负责整体的东西

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;//创建一个MainWindow类
    w.show();

    return a.exec();
}
