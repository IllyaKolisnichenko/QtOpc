#pragma once

#include "OpcUaClient.h"

#include <QObject>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow();

private:
    std::unique_ptr< OpcUaClient > opcUa_;

private slots:
    void getTagData( const QString& nodeName, const QVariant& value );
};
