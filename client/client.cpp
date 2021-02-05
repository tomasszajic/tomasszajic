/**
  @file
  @author Tomas Zajic
*/

#include <QHostAddress>

#include "mainwindow.h"
#include "client.h"

Client::Client(QObject* parent)
    : QObject(parent)
{}

void Client::createConnection(const QString deviceName,const QHostAddress host,const int port)
{
    TcpConnection* tcpConnection = new TcpConnection(deviceName, host, port, this);
    pool.append(QPointer<TcpConnection>(tcpConnection));

    connect(tcpConnection->getSocket(),SIGNAL(hostFound()),mainWindow,SLOT(slotHostFound()));
    connect(tcpConnection->getSocket(),SIGNAL(connected()),mainWindow,SLOT(slotConnected()));
    connect(tcpConnection->getSocket(),SIGNAL(disconnected()),mainWindow,SLOT(slotDisconnected()));

    tcpConnection->connectSocketToHost();
}

void Client::removeConnection(const QString deviceName)
{
    for(int i = 0;i<pool.size();i++)
    {
        if((*pool.at(i)).deviceName == deviceName)
        {
            delete pool.at(i);
            pool.removeAt(i);
        }
    }
}

void Client::createPool(const int numberConnections)
{
    pool.reserve(numberConnections);
};

void Client::setMainWindow(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

MainWindow* Client::getMainWindow() const
{
    return this->mainWindow;
}
