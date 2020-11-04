#pragma once

#include <QObject>
#include <QtOpcUa/QOpcUaProvider>
#include <QtOpcUa/QOpcUaClient>
#include <QtOpcUa/QOpcUaNode>
#include <QtOpcUa/QOpcUaEndpointDescription>

#include <memory>

class OpcUaClient : public QObject
{
    Q_OBJECT

public:
    OpcUaClient();
    ~OpcUaClient();

private:
    QOpcUaNode* boolTestNode_{};
    QOpcUaClient* client_{};
    double boolTest_{};

    void init( const QString& opcUrl );
    void connectNodes();
private slots: 
    void boolTestNodeUpdated( QOpcUa::NodeAttribute attr, const QVariant& value );
    void clientStateHandler( QOpcUaClient::ClientState state );
    void requestEndpointsFinished( const QVector<QOpcUaEndpointDescription>& endpoints );
};
