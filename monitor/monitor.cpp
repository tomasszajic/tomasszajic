/**
  @file
  @author Tomas Zajic
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "monitor.h"


Monitor::Monitor()
    : mainWindow(nullptr)
    , soket(nullptr)
{
    connect(this,SIGNAL(newConnection()),this,SLOT(createConnection()));
}

void Monitor::startListening(QHostAddress address, int port)
{
    if (!listen(address,port))
    {
        QMessageBox::critical(NULL,"Error","Monitor is not listening.");
    }
};

void Monitor::stopListening()
{
    if(this->isListening())
    {
        this->close();
    }
    for(auto elem : pool)
    {
        delete elem;
    }
    pool.clear();
}

void Monitor::createConnection()
{
    QTcpSocket* newSocket = nextPendingConnection();
    pool.append(newSocket);
    connect(newSocket, SIGNAL(readyRead()), this, SLOT(slotPacketReceived()));
}

void Monitor::slotPacketReceived()
{
    soket = qobject_cast<QTcpSocket*>(sender());
    QByteArray packetData = soket->readAll();

    /* QString stores until the first null character '\0'. */
    currentDeviceItem.name = QString(packetData.data());

    if(packetData.size() > (currentDeviceItem.name.size() +1))
    {
      /* Data is the second part of the packet terminated with null character '\0' */
      QString data(packetData.data() + currentDeviceItem.name.size()+1);
      mainWindow->setOutputText(data);
    }
    else
    {
        QString noData = "no data";
        mainWindow->setOutputText(noData);
    }

    int indexOfStoredDevice = mainWindow->deviceItems.indexOf(currentDeviceItem);

    if(indexOfStoredDevice > -1)
    {
        ++mainWindow->deviceItems[indexOfStoredDevice].packetCount;
        mainWindow->deviceItems[indexOfStoredDevice].port = soket->peerPort();
        mainWindow->updateTableRowAndStatusBar(mainWindow->deviceItems[indexOfStoredDevice], indexOfStoredDevice);
    }
    else if(indexOfStoredDevice == -1)
    {
        currentDeviceItem.port = soket->peerPort();
        mainWindow->deviceItems.append(currentDeviceItem);
        mainWindow->newTableRow(currentDeviceItem);
    };
}

void Monitor::setMainWindow(MainWindow* m)
{
    mainWindow = m;
};
