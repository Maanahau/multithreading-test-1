#ifndef IREPORT_H
#define IREPORT_H

#include <string>

class IReport
{
public:
    virtual std::string get_content() const = 0;
    virtual ~IReport() = default;
    virtual IReport* clone() const = 0;
};

#endif