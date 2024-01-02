#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include "Sensor.h"
#include "IReport.h"

#include <atomic>
#include <memory>

class TemperatureSensor final : public Sensor
{
public:

    TemperatureSensor() : Sensor(), _last_read{0.0} {};

    std::unique_ptr<IReport> create_report() override;
    void read() override;

private:

    std::atomic<double> _last_read;
};

#endif