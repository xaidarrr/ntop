#include "process.h"
#include <ncurses.h>

class NcursesRenderer {
public:
    NcursesRenderer() {
        initscr();
        cbreak();
        noecho();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
    }

    ~NcursesRenderer() {
        endwin();
    }

    void draw(std::vector<ProcessInfo>& procs);
    void handle_input(int proc_count);

private:
    int scroll_offset_ = 0;
};