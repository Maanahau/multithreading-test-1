#include "TemperatureSensor.h"

#include "TemperatureReport.h"
#include "Logger.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <cstdlib>
#include <memory>

std::unique_ptr<IReport> TemperatureSensor::create_report()
{
    const Time now = std::chrono::system_clock::now();
    const auto deltaTime = now - _last_report_time;
    const long milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count();

    _last_report_time = now;

    return std::make_unique<TemperatureReport>(_last_read, milliseconds);
}

void TemperatureSensor::read()
{
    Logger* logger = Logger::get_instance();
    while(!_must_stop)
    {
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 5));
        _last_read = rand() % 1000;

        logger->push_report(create_report());
    }
}