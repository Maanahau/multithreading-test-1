#ifndef SENSOR_H
#define SENSOR_H

#include "IReport.h"
#include "time_alias.h"

#include <chrono>
#include <mutex>
#include <atomic>
#include <memory>

class Sensor
{
public:

    inline void stop()
    {
        _must_stop = true;
    }

    virtual void read() = 0;
    virtual std::unique_ptr<IReport> create_report() = 0;

protected:

    Sensor() : _last_report_time(std::chrono::system_clock::now()), _must_stop{false} {}
    virtual ~Sensor() = default;

    Time _last_report_time;
    std::atomic<bool> _must_stop;
};

#endif