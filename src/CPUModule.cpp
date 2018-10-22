#include "CPUModule.hpp"
#include <sstream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <stdio.h>
#include <mach/mach_init.h>
#include <mach/mach_error.h>
#include <mach/mach_host.h>
#include <mach/vm_map.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

CpuModule::CpuModule()
    : IMonitorModule()
    , m_modName("CPU Module")
    , m_modData()
    , m_prevTotalTicks(0)
    , m_prevIdleTicks(0) {
    m_modData.resize(2);
}

CpuModule::~CpuModule() {

}

std::vector<std::string> const& CpuModule::GetData() const {
    return m_modData;
}

std::string const& CpuModule::GetName() const {
    return m_modName;
}

float CpuModule::CalcCPULoading(uint64_t idleTicks, uint64_t totalTicks) {
    uint64_t totalTicksSinceLastTime = totalTicks - m_prevTotalTicks;
    uint64_t idleTicksSinceLastTime  = idleTicks - m_prevIdleTicks;
    m_prevTotalTicks = totalTicks;
    m_prevIdleTicks = idleTicks;
    if (totalTicksSinceLastTime > 0) {
        return 1.0f - static_cast<float>(idleTicksSinceLastTime) / totalTicksSinceLastTime;
    } else {
        return 1.0f;
    }
}

float CpuModule::GetCPULoading() {
    host_cpu_load_info_data_t CPUInfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, reinterpret_cast<host_info_t>(&CPUInfo), &count) == KERN_SUCCESS) {
        uint64_t totalTicks = 0;
        for (int i = 0; i < CPU_STATE_MAX; i++) {
            totalTicks += CPUInfo.cpu_ticks[i];
        }
        return CalcCPULoading(CPUInfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
    } else {
        return -1.0f;
    }
}

void CpuModule::UpdateData() {
    char buf[256];
    size_t bufLen = 256;

    sysctlbyname("machdep.cpu.brand_string", &buf, &bufLen, NULL, 0);
    std::stringstream strs;
    strs << buf;
    m_modData[0] = strs.str();
    float cpuLoading = GetCPULoading() * 100.0f;
    strs.str(std::string());
    strs.precision(2);
    strs.setf(std::ios::fixed);
    strs << cpuLoading;
    m_modData[1] = strs.str();
}
