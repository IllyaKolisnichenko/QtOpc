#include "OpcUaClient.h"

#include <QCoreApplication>

void OpcUaClient::connectToOpc()
{
    QOpcUaProvider provider{};
    if ( provider.availableBackends().isEmpty() )
    {
        qDebug() << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ " " << "backends is empty";
        return;
    }

    client_ = provider.createClient( provider.availableBackends().first() );
    if ( !client_ )
    {
        qDebug() << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ " " << "can't create client";
        return;
    }

    // Connect to the stateChanged signal. Compatible slots of QObjects can be used instead of a lambda.
    connect( client_, &QOpcUaClient::stateChanged, this, &OpcUaClient::clientStateHandler );
    connect( client_, &QOpcUaClient::endpointsRequestFinished, this, &OpcUaClient::requestEndpointsFinished );
    connect( client_, &QOpcUaClient::connectError, this, &OpcUaClient::connectError );

    client_->requestEndpoints( url_ ); // Request a list of endpoints from the server
}

void OpcUaClient::connectError(QOpcUaErrorState* errorState) 
{
    qDebug() << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ " " << " connectError";
    qDebug() << "Error code - "<< errorState->errorCode();
    qDebug() << "Connection step - " << static_cast< int >( errorState->connectionStep() );
}

void OpcUaClient::requestEndpointsFinished( const QVector<QOpcUaEndpointDescription>& endpoints )
{
    if ( endpoints.isEmpty() )
    {
        qDebug() << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ " " << " The server did not return any endpoints";
        clientStateHandler( QOpcUaClient::ClientState::Disconnected );
        return;
    }
    client_->connectToEndpoint( endpoints.first() ); // First - Security policy is none 
}

void OpcUaClient::setUrl( const QString& opcUrl )
{
    url_ = opcUrl;
}

void OpcUaClient::nodeUpdated( QOpcUa::NodeAttribute attr, const QVariant& value )
{
    Q_UNUSED( attr )
    emit tagData_signal( "", value );
}

bool OpcUaClient::addTag( const QString& nodeName, const QString& tagName )
{
    bool result{ false };
    if( currentState_ == QOpcUaClient::ClientState::Connected)
    { 
        QOpcUaNode* node = client_->node( tagName );
        connect( node, &QOpcUaNode::dataChangeOccurred, this, &OpcUaClient::nodeUpdated );
        node->enableMonitoring( QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters( 100 ) );
        nodes_[ nodeName ] = node;
        result = true;
    }
    return result;
}

void OpcUaClient::clientStateHandler( QOpcUaClient::ClientState state )
{
    currentState_ = state;
    if (state == QOpcUaClient::ClientState::Connected)
        emit siemensConnected_signal();
}

OpcUaClient::~OpcUaClient()
{
    nodes_.clear();
    delete client_;
}
