#ifndef TEMPERATURE_REPORT_H
#define TEMPERATURE_REPORT_H

#include "IReport.h"

#include <string>
#include <sstream>


class TemperatureReport final : public IReport
{
public:

    TemperatureReport(double value, long millisec_waiting) : _value{value}, _millisec_waiting{millisec_waiting} {}
    TemperatureReport(const TemperatureReport&) = default;

    std::string get_content() const override
    {
        std::stringstream stream;
        stream << "Temperature: " << _value << " K | Waiting time: " << _millisec_waiting << " ms\n";
        return stream.str();
    }

    IReport* clone() const override
    {
        return new TemperatureReport(*this);
    }

private:

    const double _value;
    const long _millisec_waiting;
};

#endif