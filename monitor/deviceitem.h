/**
  @file
  @author Tomas Zajic
*/

#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QString>

class DeviceItem
{
public:
    DeviceItem(QString name = "empty", size_t packetCount = 0, quint16 port = -1);
    ~DeviceItem() = default;
    QString name;
    size_t packetCount;
    quint16 port;

    /** used for name comparison in a container */
    bool operator==(const DeviceItem& dev){return this->name == dev.name;};
};

#endif // DEVICEITEM_H
