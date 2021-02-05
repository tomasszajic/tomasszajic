/**
  @file
  @author Tomas Zajic
*/

#include "deviceitem.h"

DeviceItem::DeviceItem(QString name, size_t packetCount, quint16 port)
    : name(name)
    , packetCount(packetCount)
    , port(port)
{}
