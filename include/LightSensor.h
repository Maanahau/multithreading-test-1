#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "Sensor.h"
#include "IReport.h"

#include <atomic>
#include <memory>

class LightSensor final : public Sensor
{
public:

    LightSensor() : Sensor(), _last_read{0.0} {}

    void read() override;
    std::unique_ptr<IReport> create_report() override;

private:

    std::atomic<double> _last_read;
};

#endif