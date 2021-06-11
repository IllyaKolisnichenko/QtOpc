#include "MainWindow.h"
#include <QTimer>

MainWindow::MainWindow()
{
    opcUa = new OpcUaClient();

    opcUa->setUrl( "opc.tcp://127.0.0.1:55000" );
    opcUa->connectToOpc();

    /*QTimer::singleShot(5000, this, [this]() {
        bool result = opcUa->addTag("trigger", "ns=2;s=SIEMENSPLC.siemensplc.VIS.trigger" );
    });*/
    
    connect( opcUa, &OpcUaClient::tagData_signal, this, &MainWindow::getTagData );

}

void MainWindow::getTagData(const QString& nodeName, const QVariant& value) 
{
    Q_UNUSED(nodeName)
    qDebug() << value.toBool();
}

MainWindow::~MainWindow()
{
}
