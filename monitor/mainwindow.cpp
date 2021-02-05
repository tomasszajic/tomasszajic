/**
  @file
  @author Tomas Zajic
*/

#include "monitor.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->gridLayout);
    connect(ui->buttonStartListening,SIGNAL(clicked()),this,SLOT(buttonListen()));

    ui->buttonStartListening->setCheckable(true);
    ui->buttonStartListening->setStyleSheet("QPushButton:checked{background-color:green;}");

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(3);

    ui->statusBar->showMessage("Packets received: 0");

    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(0,QHeaderView::Stretch);
    header->setSectionResizeMode(1,QHeaderView::Stretch);
    header->setSectionResizeMode(2,QHeaderView::Stretch);
    QStringList tableHeader = {"Device name", "port", "packets"};
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    ui->tableWidget->setShowGrid(true);

}

void MainWindow::buttonListen()
{
    if(ui->buttonStartListening->isChecked())
    {
        int port = ui->linePort->text().toInt();
        QHostAddress address(ui->lineIp->text());
        ui->buttonStartListening->setText("Stop");
        monitor->startListening(address,port);
    }
    else
    {
        ui->buttonStartListening->setText("Listen");
        monitor->stopListening();
    }
};

void MainWindow::updateTableRowAndStatusBar(DeviceItem& deviceItem,const int row)
{
    static int totalPacketCount = 0;
    ++totalPacketCount;
    ui->statusBar->showMessage("Packets received: "+QString::number(totalPacketCount));
    ui->tableWidget->item(row, PACKETS)->setData(Qt::DisplayRole,deviceItem.packetCount);
    ui->tableWidget->item(row, PORT)->setData(Qt::DisplayRole,deviceItem.port);
};

void MainWindow::newTableRow(DeviceItem& deviceItem)
{
    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(rowCount+1);

    ui->tableWidget->setItem(rowCount,0,new QTableWidgetItem(deviceItem.name));
    ui->tableWidget->setItem(rowCount,1,new QTableWidgetItem(QString::number(deviceItem.port)));
    ui->tableWidget->setItem(rowCount,2,new QTableWidgetItem(QString::number(deviceItem.packetCount)));
};

void MainWindow::setOutputText(QString& data)
{
    ui->textOutput->setPlainText(data);
}

void MainWindow::setMonitor(Monitor* m)
{
    monitor = m;
};

MainWindow::~MainWindow()
{
    delete ui;
}

