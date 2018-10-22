#ifndef APP_HPP
# define APP_HPP

# include "IMonitorModule.hpp"
# include "IMonitorDisplay.hpp"

class App {
public:
    App();
    ~App();

    void MainLoop();
private:
    void ProcessEvent(UIEvent const &e);

private:
    bool m_quit;
    IMonitorDisplay *m_interface;
    std::vector<IMonitorModule*> m_modules;
};

#endif
