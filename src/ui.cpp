#include "ui.h"

#ifdef __ANDROID__
    #include <curses.h>
#else
    #include <ncurses.h>
#endif

NcursesRenderer::NcursesRenderer() : scroll_offset_{0} {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

NcursesRenderer::~NcursesRenderer() {
    endwin();
}

void NcursesRenderer::handle_input(int proc_count) {
    int visible = LINES - 3;
    int ch = 0;
    while((ch = getch()) != ERR) {
        switch (ch) {
            case KEY_UP:
                if (scroll_offset_ > 0) scroll_offset_--;
                break;
            case KEY_DOWN:
                if (scroll_offset_ + visible < proc_count) scroll_offset_++;
                break;
        }   
    }
    
}

void NcursesRenderer::draw(std::vector<ProcessInfo>& procs) {
    erase();
    attron(A_BOLD);
    mvprintw(0, 0, "%-6s %-32s %10s %8s %8s %12s", "PID", "NAME", "STATE", "CPU%", "MEM%", "MEM (MB)");
    attroff(A_BOLD);

    int maxRows = LINES - 3;
    for (int i = 0; i < maxRows; i++) {
        int idx = scroll_offset_ + i;
        if (idx >= (int)procs.size()) break;

        mvprintw(i + 2, 0, "%-6d %-32s %6s %11.1f%% %7.1f%% %6d",
            procs[idx].get_pid(), procs[idx].get_name().c_str(),
            procs[idx].get_state().c_str(), procs[idx].get_cpu_percent(),
            procs[idx].get_mem_percent(), procs[idx].get_virt_mem()
        );
    }

    refresh();
}