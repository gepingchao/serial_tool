#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "serial_tool.h"
class SleeperThread : public QThread
{
public:
static void msleep(unsigned long msecs)
{
QThread::msleep(msecs);
}
};

#endif // PROTOCOL_H
