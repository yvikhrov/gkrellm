#ifndef HOSTNAMEUSERNAMEMODULE_HPP
# define HOSTNAMEUSERNAMEMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class HostnameUsernameModule : public IMonitorModule {
public:
    virtual ~HostnameUsernameModule();
    HostnameUsernameModule();
    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:
    std::string const m_modName;
    std::vector<std::string> m_modData;
};

#endif
