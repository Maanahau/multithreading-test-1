#ifndef ILOG_SINK_H
#define ILOG_SINK_H

#include "IReport.h"

#include <queue>

class ILogSink
{
public:
    virtual void log(IReport* const report) = 0;
    virtual ~ILogSink() = default;
};

#endif