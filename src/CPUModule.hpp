#ifndef CPUMODULE_HPP
# define CPUMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class CpuModule : public IMonitorModule {
public:
    virtual ~CpuModule();
    CpuModule();

    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:
    float CalcCPULoading(uint64_t iTicks, uint64_t tTicks);
    float GetCPULoading();

private:
    std::string const m_modName;
    std::vector<std::string> m_modData;
    uint64_t m_prevTotalTicks;
    uint64_t m_prevIdleTicks;
};

#endif
