#include <ctime>
#include <sstream>
#include <iomanip>
#include "DateTimeModule.hpp"

DateTimeModule::DateTimeModule()
    : IMonitorModule()
    , m_modName("Date&Time module")
    , m_modData() {
    m_modData.resize(1);
}

DateTimeModule::~DateTimeModule() {

}

std::vector<std::string> const& DateTimeModule::GetData() const {
    return m_modData;
}

std::string const& DateTimeModule::GetName() const {
    return m_modName;
}

void DateTimeModule::UpdateData() {
    time_t tm = time(0);
    struct tm * tmpNow = localtime( & tm );

    std::stringstream ss;
    ss << (tmpNow->tm_year + 1900) << '-' << (tmpNow->tm_mon + 1) << '-' <<  tmpNow->tm_mday << ' ' << tmpNow->tm_hour << ':';
    ss << std::setfill('0') << std::setw(2) << tmpNow->tm_min << ':';
    ss << std::setfill('0') << std::setw(2) << tmpNow->tm_sec;
    m_modData[0] = ss.str();
}
