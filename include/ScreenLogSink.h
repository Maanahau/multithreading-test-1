#ifndef SCREEN_LOG_SINK
#define SCREEN_LOG_SINK

#include "ILogSink.h"
#include "IReport.h"

#include <iostream>

class ScreenLogSink final : public ILogSink
{
public:
    void log(IReport* const report) override
    {
        std::cout << report->get_content();
    };
};

#endif