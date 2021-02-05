/**
  @file
  @author Tomas Zajic
*/

#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QObject>
#include <QByteArray>
#include <QHostAddress>
#include "datagenerator.h"

class QTcpSocket;

class TcpConnection : public QObject
{
    Q_OBJECT
public:
    TcpConnection(QString deviceName, QHostAddress host, int port, QObject *parent = nullptr);
    ~TcpConnection();

    /** create a connection to a host */
    void connectSocketToHost();
    QTcpSocket* getSocket();
    QString deviceName;
    QHostAddress host;
    int port;

public slots:
    void writeToSocketTimeout();

private:
    /** mimics data generated from a device */
    DataGenerator* dataGenerator;

    /** triggers sending a packet in a time period */
    QTimer timer;

    /** realizes a connection to a host*/
    QTcpSocket* tcpSocket;

    /** data to be sent by tcpSocket */
    QByteArray buffer;
};

#endif // TCPCONNECTION_H
