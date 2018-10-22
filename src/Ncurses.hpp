#ifndef NCURSES_HPP
# define NCURSES_HPP

# include "IMonitorDisplay.hpp"

class Ncurses : public IMonitorDisplay {
public:
    Ncurses();
    ~Ncurses();

    void Update(std::vector<IMonitorModule*>& modules);
    bool PollEvent(UIEvent &event);
    void Render();
};

#endif
