/**
  @file
  @author Tomas Zajic
*/

#ifndef MONITOR_H
#define MONITOR_H

#include <QtNetwork>
#include <QMessageBox>
#include "deviceitem.h"

class MainWindow;

class Monitor : public QTcpServer
{
    Q_OBJECT
public:
    Monitor();
    ~Monitor() = default;
    void setMainWindow(MainWindow* mainWindow);

public slots:
    void createConnection();
    void slotPacketReceived();
    void startListening(QHostAddress address, int port);
    void stopListening();

private:
    MainWindow* mainWindow;
    /** temporary packet data */
    DeviceItem currentDeviceItem;
    /** pool of all connections */
    QList<QTcpSocket*> pool;
    /** a connection */
    QTcpSocket* soket;
};

#endif // MONITOR_H

