/**
  @file
  @author Tomas Zajic
*/

#include "mainwindow.h"
#include "monitor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Monitor monitor;
    MainWindow mainWindow;
    monitor.setMainWindow(&mainWindow);
    mainWindow.setMonitor(&monitor);
    mainWindow.show();

    return a.exec();
}
