#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();  //打开主窗口

    return a.exec();  //执行程序直到窗口关闭
}
