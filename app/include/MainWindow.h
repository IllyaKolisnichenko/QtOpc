#pragma once
#include "OpcUaClient.h"
#include <QObject>

class MainWindow : public QObject
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
private:
    OpcUaClient* opcUa{};
private slots:
    void getTagData(const QString& nodeName, const QVariant& value);
};
