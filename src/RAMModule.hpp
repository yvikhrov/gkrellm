#ifndef RAMMODULE_HPP
# define RAMMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class RAMModule : public IMonitorModule {
public:
    virtual ~RAMModule();
    RAMModule();

    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:
    std::string const m_modName;
    std::vector<std::string> m_modData;
};

#endif
