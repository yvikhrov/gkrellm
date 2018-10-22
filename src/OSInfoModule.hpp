#ifndef OSINFOMODULE_HPP
# define OSINFOMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class OSInfoModule : public IMonitorModule  {
public:
    virtual ~OSInfoModule();
    OSInfoModule();

    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:
    std::string const m_modName;
    std::vector<std::string> m_modData;
};

#endif
