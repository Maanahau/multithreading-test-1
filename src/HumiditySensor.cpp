#include "HumiditySensor.h"

#include "HumidityReport.h"
#include "Logger.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <memory>

std::unique_ptr<IReport> HumiditySensor::create_report()
{
    const Time now = std::chrono::system_clock::now();
    const auto deltaTime = now - _last_report_time;
    const long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    _last_report_time = now;

    return std::make_unique<HumidityReport>(_last_read, milliseconds);
}

void HumiditySensor::read()
{
    Logger* logger = Logger::get_instance();
    while(!_must_stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
        _last_read = (rand() % 100) / 100.0;

        logger->push_report(create_report());
    }
}