#include "process.h"
#include <ncurses.h>

class NcursesRenderer {
public:
    NcursesRenderer() {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
    }

    ~NcursesRenderer() {
        endwin();
    }

    void draw(std::vector<ProcessInfo>& procs);
};