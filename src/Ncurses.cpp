#include "Ncurses.hpp"
#include <ncurses.h>
#include "IMonitorModule.hpp"
#include <iostream>

Ncurses::Ncurses() {
    initscr();
    noecho();
    timeout(0);
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_CYAN);
}

Ncurses::~Ncurses() {
    endwin();
}

void Ncurses::Update(std::vector<IMonitorModule*>& modules) {
    int offset = 0;
    int width;
    int height;

    getmaxyx(stdscr, height, width);
    std::vector<IMonitorModule*>::iterator it;
    for (it = modules.begin(); it != modules.end(); ++it) {
        (*it)->UpdateData();

        attron(COLOR_PAIR(2));
        mvprintw(offset++, 0, "%*s", width, "");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(2));
        mvprintw(offset, 0, "  ");
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(1));
        mvprintw(offset++, 3, (*it)->GetName().c_str());
        attroff(COLOR_PAIR(1));

        std::vector<std::string> data = (*it)->GetData();
        for (size_t i = 0; i < data.size(); ++i) {
            attron(COLOR_PAIR(2));
            mvprintw(offset, 0, "  ");
            attroff(COLOR_PAIR(2));
            mvprintw(offset++, 5, data[i].c_str());
        }
    }

    attron(COLOR_PAIR(2));
    mvprintw(offset++, 0, "%*s", width, "");
    attroff(COLOR_PAIR(2));
}

bool Ncurses::PollEvent(UIEvent &event) {
    int e = getch();
    if (e == 27) {
        return event.type = kEventQuit;
    } else if (e == 's') {
        return event.type = kEventSwitch;
    }
    return false;
}

void Ncurses::Render() {
    refresh();
}
