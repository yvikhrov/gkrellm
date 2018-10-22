#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

#include <iostream>
#include <vector>

class IMonitorModule {
public:
    virtual ~IMonitorModule() {}
    virtual void UpdateData() = 0;
    virtual std::string const& GetName() const = 0;
    virtual std::vector<std::string> const& GetData() const = 0;
};

#endif