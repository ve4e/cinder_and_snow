#include "Mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/main/main.png"));

    MainWindow w;
    w.show();

    return a.exec();
}
