/**
  @file
  @author Tomas Zajic
*/

#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <QByteArray>
#include <QTimer>
#include <QObject>

class DataGenerator : public QObject
{
    Q_OBJECT
public:
    DataGenerator(QByteArray& buffer,const QString name);
    ~DataGenerator();

    void prependDeviceName();
    void start();
    void stop();

public slots:
    void generator();

private:
    QByteArray& buffer;
    QString deviceName;
    QTimer timer;
};

#endif // DATAGENERATOR_H
