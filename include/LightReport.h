#ifndef LIGHT_REPORT_H
#define LIGHT_REPORT_H

#include "IReport.h"

#include <chrono>
#include <string>
#include <sstream>

class LightReport final : public IReport
{
public:

    LightReport(double value, long millisec_waiting) : _value(value), _millisec_waiting(millisec_waiting) {}
    LightReport(const LightReport&) = default;

    std::string get_content() const override
    {
        std::stringstream stream;
        stream << "Light: " << _value << " cd | Waiting time: " << _millisec_waiting << " ms\n";
        return stream.str();
    }

    IReport* clone() const override
    {
        return new LightReport(*this);
    }

private:

    const double _value;
    const long _millisec_waiting;
};

#endif