#pragma once

#include <QObject>
#include <QtOpcUa/QOpcUaProvider>
#include <QtOpcUa/QOpcUaClient>
#include <QtOpcUa/QOpcUaNode>
#include <QtOpcUa/QOpcUaEndpointDescription>
#include <QtOpcUa/QOpcUaErrorState>

#include <memory>

class OpcUaClient : public QObject
{
    Q_OBJECT

public:
    OpcUaClient() = default;
    ~OpcUaClient();
    bool addTag( const QString& nodeName, const QString& tagName );
    void setUrl( const QString& url );
    void connectToOpc();
private:
    QOpcUaClient* client_{};
    QMap< QString, QOpcUaNode* > nodes_; //key - tag name, value - node
    QOpcUaClient::ClientState currentState_{ QOpcUaClient::ClientState::Closing };
    QString url_{};
    QOpcUaPkiConfiguration pkiConfig;
private slots: 
    void nodeUpdated( QOpcUa::NodeAttribute attr, const QVariant& value );
    void clientStateHandler( QOpcUaClient::ClientState state );
    void requestEndpointsFinished( const QVector<QOpcUaEndpointDescription>& endpoints );
    void connectError( QOpcUaErrorState* errorState );
signals:
    void tagData_signal( QString nodeName, QVariant value );
    void siemensConnected_signal();
};
