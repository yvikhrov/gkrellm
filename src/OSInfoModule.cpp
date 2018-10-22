#include "OSInfoModule.hpp"
#include <sstream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>

OSInfoModule::OSInfoModule()
    : IMonitorModule()
    , m_modName("OS info")
    , m_modData() {
    m_modData.resize(2);
}

OSInfoModule::~OSInfoModule() {

}

std::vector<std::string> const& OSInfoModule::GetData() const {
    return m_modData;
}

std::string const& OSInfoModule::GetName() const {
    return m_modName;
}

void OSInfoModule::UpdateData() {
    char buf[255];
    size_t bufLen = 255;

    std::stringstream strs;
    sysctlbyname("kern.ostype", &buf, &bufLen, NULL, 0);
    strs << "OS type: " << buf;
    m_modData[0] = strs.str();
    strs.str(std::string());
    sysctlbyname("kern.osrelease", &buf, &bufLen, NULL, 0);
    strs << "OS release: " << buf;
    m_modData[1] = strs.str();
}
