#ifndef NETWORKMODULE_HPP
# define NETWORKMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class NetMonitorModule : public IMonitorModule {
public:
    virtual ~NetMonitorModule();
    NetMonitorModule();

    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:    
    std::string const m_modName;
    std::vector<std::string> m_modData;
};

#endif
