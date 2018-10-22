#ifndef DATETIMEMODULE_HPP
# define DATETIMEMODULE_HPP

# include <vector>
# include "IMonitorModule.hpp"

class DateTimeModule : public IMonitorModule {
public:
    virtual ~DateTimeModule();
    DateTimeModule();

    void UpdateData();
    std::string const& GetName() const;
    std::vector<std::string> const& GetData() const;
private:    
    std::string const m_modName;
    std::vector<std::string> m_modData;
};

#endif
