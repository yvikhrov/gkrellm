#include "App.hpp"
#include "Ncurses.hpp"
#include "SDL.hpp"
#include "CPUModule.hpp"
#include "RAMModule.hpp"
#include "DateTimeModule.hpp"
#include "NetworkModule.hpp"
#include "OSInfoModule.hpp"
#include "HostnameUsernameModule.hpp"
#include <unistd.h>

App::App()
    : m_quit(false)
    , m_interface(new Ncurses) {

    m_modules.push_back(new CpuModule());
    m_modules.push_back(new DateTimeModule());
    m_modules.push_back(new HostnameUsernameModule());
    m_modules.push_back(new OSInfoModule());
    m_modules.push_back(new RAMModule());
    m_modules.push_back(new NetMonitorModule());
}

App::~App() {
    delete m_interface;
    for (size_t i = 0; i < m_modules.size(); ++i) {
        delete m_modules[i];
    }
}

void App::ProcessEvent(UIEvent const &e) {
    if (e.type == kEventQuit) {
        m_quit = true;
    } else if (e.type == kEventSwitch) {
        bool isNcurses = dynamic_cast<Ncurses*>(m_interface) != NULL;
        delete m_interface;
        if (isNcurses) {
            m_interface = new SDL;
        } else {
            m_interface = new Ncurses;
        }
    }
}

void App::MainLoop() {
    UIEvent e;
    while (!m_quit) {
        while (m_interface->PollEvent(e)) {
            ProcessEvent(e);
        }
        m_interface->Update(m_modules);
        m_interface->Render();
    }
}
