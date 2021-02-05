/**
  @file
  @author Tomas Zajic
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
/**
  @file
  @author Tomas Zajic
*/

#include <QLabel>
#include "deviceitem.h"

enum HeaderItems{
    DEVICE_NAME,
    PORT,
    PACKETS
};

class Monitor;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMonitor(Monitor* monitor);
    void setOutputText(QString& data);
    void newTableRow(DeviceItem& deviceItem);
    void updateTableRowAndStatusBar(DeviceItem& deviceItem,const int row);

    /** for storing information about each device that made a connection*/
    QVector<DeviceItem> deviceItems;

public slots:
    void buttonListen();

private:
    Ui::MainWindow* ui;
    Monitor* monitor;
};

#endif // MAINWINDOW_H
