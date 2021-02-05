/**
  @file
  @author Tomas Zajic
*/

#include "datagenerator.h"

DataGenerator::DataGenerator(QByteArray& buffer,const QString deviceName)
    : buffer(buffer)
    , deviceName(deviceName)
{
    srand(time(NULL));
    timer.setInterval(20);
    connect(&timer,SIGNAL(timeout()),this,SLOT(generator()));
}

DataGenerator::~DataGenerator()
{
    if(timer.isActive())
    {
        timer.stop();
    };
}

void DataGenerator::prependDeviceName()
{
    for(int i = 0;i<deviceName.size();i++)
    {
        buffer[i] = deviceName.at(i).toLatin1();
    }
    buffer[deviceName.size()] = '\0';
};

void DataGenerator::generator()
{
    int amount = (std::rand() % 9);
    buffer.append(QString::number(amount));
}

void DataGenerator::start()
{
    prependDeviceName();
    timer.start();
}

void DataGenerator::stop()
{
    if(timer.isActive())
    {
        timer.stop();
    };
}
