#include <QtCore/QCoreApplication>
#include "OpcUaClient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    OpcUaClient opcUa;
    return a.exec();
}
