#include <QtGui/QApplication>
#include "mainwindow.hh"

//using namespace Ui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
