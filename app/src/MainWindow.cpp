#include "MainWindow.h"
#include <QTimer>

MainWindow::MainWindow()
{
    opcUa_ = std::make_unique< OpcUaClient >();
    opcUa_->setUrl( "opc.tcp://127.0.0.1:55000" );
    opcUa_->connectToOpc();
    //opcUa->addTag("trigger", "ns=2;s=Siemensplc.Data_DB.trigger" );
    
    connect( opcUa_.get(), &OpcUaClient::tagData_signal, this, &MainWindow::getTagData );
}

void MainWindow::getTagData(const QString& nodeName, const QVariant& value) 
{
    Q_UNUSED(nodeName)
    qDebug() << value.toString();
}
