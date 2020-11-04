#include "OpcUaClient.h"

OpcUaClient::OpcUaClient()
{
    // type URL "opc.tcp://ip_opc:port_opc"
    init( "opc.tcp://192.168.137.1:55000" );
}

void OpcUaClient::init( const QString& opcUrl )
{
    QOpcUaProvider provider{};
    if ( provider.availableBackends().isEmpty() )
        return;

    client_ = provider.createClient( provider.availableBackends().first() );
    if ( !client_ )
        return;

    // Connect to the stateChanged signal. Compatible slots of QObjects can be used instead of a lambda.
    connect( client_, &QOpcUaClient::stateChanged, this, &OpcUaClient::clientStateHandler );
    connect( client_, &QOpcUaClient::endpointsRequestFinished, this, &OpcUaClient::requestEndpointsFinished );

    client_->requestEndpoints( QUrl( opcUrl ) ); // Request a list of endpoints from the server
}

void OpcUaClient::requestEndpointsFinished( const QVector<QOpcUaEndpointDescription>& endpoints )
{
    if ( endpoints.isEmpty() )
    {
        qDebug() << "The server did not return any endpoints";
        clientStateHandler( QOpcUaClient::ClientState::Disconnected );
        return;
    }
    client_->connectToEndpoint( endpoints.first() );
}

void OpcUaClient::connectNodes()
{
    connect( boolTestNode_, &QOpcUaNode::dataChangeOccurred, this, &OpcUaClient::boolTestNodeUpdated );
}

void OpcUaClient::boolTestNodeUpdated( QOpcUa::NodeAttribute attr, const QVariant& value )
{
    Q_UNUSED(attr);
    qDebug() << value.toBool();
    //write value in node
    //uncomment, for test write
    //if (m_boolTestNode)
    //    m_boolTestNode->writeAttribute( QOpcUa::NodeAttribute::Value, !value.toBool() );
}

void OpcUaClient::clientStateHandler( QOpcUaClient::ClientState state )
{
    if ( state == QOpcUaClient::ClientState::Connected ) {
        qDebug()<< "Connected";
        // Create node objects for reading, writing and subscriptions
        // ns=2 is indicating namespace index 2
        // s=SIEMENSPLC.siemensplc.BOOL_TEST - test tag. Get from OPC
        boolTestNode_ = client_->node("ns=2;s=SIEMENSPLC.siemensplc.BOOL_TEST" );

        // Connect signal handlers for subscribed values
        QObject::connect( boolTestNode_, &QOpcUaNode::dataChangeOccurred, this, &OpcUaClient::boolTestNodeUpdated );

        // Subscribe to data changes
        boolTestNode_->enableMonitoring( QOpcUa::NodeAttribute::Value, QOpcUaMonitoringParameters( 100 ) );
    }

    if ( state == QOpcUaClient::ClientState::Connecting )
        qDebug()<< "Connecting";

    if ( state == QOpcUaClient::ClientState::Disconnected )
        qDebug() << "Disconnected";
}

OpcUaClient::~OpcUaClient()
{
    delete boolTestNode_;
    delete client_;
}
