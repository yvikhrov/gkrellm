#include "RAMModule.hpp"
#include <sstream>
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <math.h>
#include <sys/ioctl.h>
#include <unistd.h>

RAMModule::RAMModule()
    : IMonitorModule()
    , m_modName("RAM Module")
    , m_modData() {
    m_modData.resize(1);
}

RAMModule::~RAMModule() {

}

std::vector<std::string> const& RAMModule::GetData() const {
    return m_modData;
}

std::string const& RAMModule::GetName() const {
    return m_modName;
}

void RAMModule::UpdateData() {
    u_int64_t memory;
    float memoryFactor = 0.0;
    vm_size_t pageSize;
    vm_statistics_data_t vm;
    int m[] = {CTL_HW, HW_MEMSIZE};
    size_t len = sizeof(memory);
    sysctl(m, 2, &memory, &len, NULL, 0);

    mach_port_t mPort = mach_host_self(); 
    mach_msg_type_number_t num = sizeof(vm) / sizeof(natural_t);
    if (KERN_SUCCESS == host_page_size(mPort, &pageSize) &&
        KERN_SUCCESS == host_statistics(mPort, HOST_VM_INFO, reinterpret_cast<host_info_t>(&vm), &num)) {
        memoryFactor = static_cast<float>(( vm.active_count + vm.wire_count ) * pageSize);
    }
    std::stringstream ss; 
    ss << static_cast< int >(memoryFactor / 1024 / 1024) << "/" << static_cast< int >(memory / 1024 / 1024);
    m_modData[0] = ss.str();
}
