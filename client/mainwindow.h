/**
  @file
  @author Tomas Zajic
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum HeaderItems{
    DEVICE_NAME,
    HOST_IP,
    PORT,
    BUTTON_STREAMING,
    STATUS
};

class QTableWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Client* client, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createDevices();
    void buttonStartClicked();
    void slotHostFound();
    void slotConnected();
    void slotDisconnected();

private:
    int findRowWithDeviceName(QString& senderDeviceName);

    Ui::MainWindow *ui;
    Client* client;
};

#endif // MAINWINDOW_H
