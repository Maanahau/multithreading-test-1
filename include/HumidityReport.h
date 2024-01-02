#ifndef HUMIDITY_REPORT_H
#define HUMIDITY_REPORT_H

#include "IReport.h"

#include <string>
#include <sstream>


class HumidityReport final : public IReport
{
public:

    HumidityReport(double value, long millisec_waiting) : _value{value}, _millisec_waiting{millisec_waiting} {}
    HumidityReport(const HumidityReport&) = default;

    std::string get_content() const override
    {
        std::stringstream stream;
        stream << "Humidity: " << _value << " % | Waiting time: " << _millisec_waiting << " ms\n";
        return stream.str();
    }

    IReport* clone() const override
    {
        return new HumidityReport(*this);
    }

private:

    const double _value;
    const long _millisec_waiting;
};

#endif