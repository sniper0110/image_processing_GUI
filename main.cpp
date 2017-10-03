#include "mainwindow.h"
#include <QApplication>

#include <QGraphicsScene>
#include <QLabel>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //input_Form i;
    w.show();
    //i.show();



    return a.exec();
}
