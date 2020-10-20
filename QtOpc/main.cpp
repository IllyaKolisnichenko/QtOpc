#include <QtCore/QCoreApplication>
#include <QtOpcUa/QOpcUaProvider>
#include <QtOpcUa/QOpcUaClient>
#include <QtOpcUa/QOpcUaNode>
#include <QtOpcUa/QOpcUaEndpointDescription>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QOpcUaProvider provider;
    if (provider.availableBackends().isEmpty())
        return 1;

    QOpcUaClient *client = provider.createClient(provider.availableBackends()[0]);
    if (!client)
        return 1;

    // Connect to the stateChanged signal. Compatible slots of QObjects can be used instead of a lambda.
    QObject::connect(client, &QOpcUaClient::stateChanged, [client](QOpcUaClient::ClientState state) {
        qDebug() << "Client state changed:" << state;
        if (state == QOpcUaClient::ClientState::Connected) {
            QOpcUaNode *node = client->node("ns=0;i=84");
            if (node)
                qDebug() << "A node object has been created";
        }
    });

    QObject::connect(client, &QOpcUaClient::endpointsRequestFinished,
        [client](QVector<QOpcUaEndpointDescription> endpoints) {
        qDebug() << "Endpoints returned:" << endpoints.count();
        if (endpoints.size())
            client->connectToEndpoint(endpoints.first()); // Connect to the first endpoint in the list
    });

    client->requestEndpoints(QUrl("opc.tcp://127.0.0.1:55000")); // Request a list of endpoints from the server

    return a.exec();
}
