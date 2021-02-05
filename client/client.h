/**
  @file
  @author Tomas Zajic
*/

#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QPointer>
#include "tcpconnection.h"

class MainWindow;

class Client : public QObject
{
    Q_OBJECT
public:
    Client(QObject* parent = nullptr);
    ~Client() = default;

    void createPool(int numberConnections);
    void createConnection(const QString deviceName,const QHostAddress host,const int port);
    void removeConnection(const QString deviceName);
    void setMainWindow(MainWindow* mainWindow);
    MainWindow* getMainWindow() const;

private:
    /** Qt containers can store only assignable data types. Therefore shared_ptr or QPointer can be used instead of unique_ptr */
    QList<QPointer<TcpConnection>> pool;

    MainWindow* mainWindow;
};

#endif // CLIENT_H
