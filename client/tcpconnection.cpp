/**
  @file
  @author Tomas Zajic
*/

#include "tcpconnection.h"
#include "mainwindow.h"
#include "client.h"
#include <QTcpSocket>
#include <QDataStream>

TcpConnection::TcpConnection(QString deviceName, QHostAddress host, int port, QObject *parent)
    : QObject(parent)
    , deviceName(deviceName)
    , host(host)
    , port(port)
    , dataGenerator(nullptr)
{
    tcpSocket = new QTcpSocket;
    buffer.reserve(10000);
    dataGenerator = new DataGenerator(buffer, deviceName);
    tcpSocket->setProperty("deviceName",deviceName);
    timer.setInterval(500);

    connect(&timer,SIGNAL(timeout()),this,SLOT(writeToSocketTimeout()));   
}

TcpConnection::~TcpConnection()
{
    dataGenerator->stop();
    if(timer.isActive())
    {
        timer.stop();
    };

    if(tcpSocket != nullptr)
    {
        if(tcpSocket->isOpen())
        {
            tcpSocket->close();
        }
        delete tcpSocket;
    }
};

void TcpConnection::connectSocketToHost()
{
    tcpSocket->connectToHost(host,port);

    dataGenerator->start();
    timer.start();
}

void TcpConnection::writeToSocketTimeout()
{
    tcpSocket->write(buffer);
    buffer.clear();
    dataGenerator->prependDeviceName();
}

QTcpSocket* TcpConnection::getSocket()
{
    return tcpSocket;
};

