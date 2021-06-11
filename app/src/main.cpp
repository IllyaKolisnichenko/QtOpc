#include <QtCore/QCoreApplication>
#include <QFileDialog>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    MainWindow opcUa;

    return a.exec();
}
