#include "HostnameUsernameModule.hpp"
#include <sstream>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>

HostnameUsernameModule::HostnameUsernameModule()
    : IMonitorModule()
    , m_modName("Host module")
    , m_modData() {
    m_modData.resize(2);
}

HostnameUsernameModule::~HostnameUsernameModule() {

}

std::vector<std::string> const& HostnameUsernameModule::GetData() const {
    return m_modData;
}

std::string const& HostnameUsernameModule::GetName() const {
    return m_modName;
}

void HostnameUsernameModule::UpdateData() {
    struct passwd *pas;
    char buf[255];
    size_t bufLen = 255;

    pas = getpwuid(getuid());
    std::stringstream strs;
    strs << "User: " << pas->pw_name;
    m_modData[0] = strs.str();
    strs.str(std::string());
    sysctlbyname("kern.hostname", &buf, &bufLen, NULL, 0);
    strs << "Hostname: " << buf;
    m_modData[1] = strs.str();
}
