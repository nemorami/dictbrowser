#include "mainwindow.h"

#include <QApplication>
/* in qtcreator */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
