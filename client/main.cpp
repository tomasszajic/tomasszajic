/**
  @file
  @author Tomas Zajic
*/

#include <QApplication>
#include "mainwindow.h"
#include "client.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);

    Client client;
    MainWindow mainWindow(&client);
    mainWindow.show();

    return app.exec();
}
