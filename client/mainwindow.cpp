/**
  @file
  @author Tomas Zajic
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QHostAddress>


MainWindow::MainWindow(Client* client, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(client)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->gridLayout);
    client->setMainWindow(this);


    connect(ui->btnCreateDevices,SIGNAL(clicked()),this,SLOT(createDevices()));

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setShowGrid(true);

    QHeaderView* header = ui->tableWidget->horizontalHeader();
    QStringList tableHeader = {"Device name", "Host IP address", "  Port  ", "Streaming", "Status"};
    header->setSectionResizeMode(DEVICE_NAME, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(HOST_IP, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(PORT, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(BUTTON_STREAMING, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(STATUS, QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
}

void MainWindow::buttonStartClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    Q_ASSERT_X(button, "MainWindow::tableItemClicked", "pointer is not initialized");

    if (button)
    {
        QHostAddress hostAddress;
        int row = button->property("row").toInt();
        int port = ui->tableWidget->item(row,PORT)->text().toInt();

        hostAddress.setAddress(ui->tableWidget->item(row,HOST_IP)->text());
        QString deviceName = ui->tableWidget->item(row,DEVICE_NAME)->text();

        if(button->isChecked())
        {
            button->setText("Stop");
            client->createConnection(deviceName, hostAddress, port);
        }
        else
        {
            client->removeConnection(deviceName);
            button->setText("Start");
        }
    }
};

void MainWindow::createDevices()
{
    int numberOfDevices = ui->numberDevices->value();
    QString hostname = ui->hostIP->displayText();
    qDebug()<<ui->tableWidget->rowCount();

    if(numberOfDevices == 0)
    {
        QMessageBox::warning(this, "Client","The number of devices must be non-zero.", QMessageBox::Ok);
    }
    else if(hostname == QString(""))
    {
        QMessageBox::warning(this, "Client","Host IP must be filled.", QMessageBox::Ok);
    }
    else if(ui->tableWidget->rowCount())
    {
        QMessageBox::warning(this, "Client","The table already contains devices.\nRestart the client.", QMessageBox::Ok);
    }
    else
    {
        ui->tableWidget->setRowCount(numberOfDevices);

        for(int i=0; i<numberOfDevices; ++i)
        {
            QString defaultName("Device"+QString::number(i));
            QPushButton* btnStart = new QPushButton("Start");
            btnStart->setProperty("row", i);
            btnStart->setCheckable(true);
            btnStart->setStyleSheet("QPushButton:checked{background-color:green;}");
            ui->tableWidget->setItem(i, DEVICE_NAME,new QTableWidgetItem(defaultName));
            ui->tableWidget->setItem(i, HOST_IP,new QTableWidgetItem(ui->hostIP->text()));
            ui->tableWidget->setItem(i, PORT,new QTableWidgetItem("5001"));
            ui->tableWidget->setCellWidget(i, BUTTON_STREAMING,btnStart);
            ui->tableWidget->setItem(i, STATUS,new QTableWidgetItem("no status"));
            connect(btnStart,SIGNAL(clicked()),this,SLOT(buttonStartClicked()));
        }
        client->createPool(numberOfDevices);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::findRowWithDeviceName(QString& senderDeviceName)
{
    for(int i = 0;i<ui->tableWidget->rowCount();i++)
    {
        if(senderDeviceName == ui->tableWidget->item(i, DEVICE_NAME)->text())
        {
            return i;
        }
    }
}

void MainWindow::slotHostFound()
{
    QString senderDeviceName = qobject_cast<QTcpSocket*>(sender())->property("deviceName").toString();
    int row = findRowWithDeviceName(senderDeviceName);
    ui->tableWidget->item(row, STATUS)->setText("Host found");
};

void MainWindow::slotConnected()
{
    QString senderDeviceName = qobject_cast<QTcpSocket*>(sender())->property("deviceName").toString();
    int row = findRowWithDeviceName(senderDeviceName);
    ui->tableWidget->item(row, STATUS)->setText("Connected");
};

void MainWindow::slotDisconnected()
{
    QString senderDeviceName = qobject_cast<QTcpSocket*>(sender())->property("deviceName").toString();
    int row = findRowWithDeviceName(senderDeviceName);
    ui->tableWidget->item(row, STATUS)->setText("Disconnected");
};
