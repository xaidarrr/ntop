#include "ui.h"

void NcursesRenderer::handle_input(int proc_count) {
    int visible = LINES - 3;
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            if (scroll_offset_ > 0) scroll_offset_--;
            break;
        case KEY_DOWN:
            if (scroll_offset_ + visible < proc_count) scroll_offset_++;
            break;
    }   
    
    while(getch() != ERR);
}

void NcursesRenderer::draw(std::vector<ProcessInfo>& procs) {
    clear();
    attron(A_BOLD);
    mvprintw(0, 0, "%-6s %-32s %10s %12s", "PID", "NAME", "STATE", "MEM (MB)");
    attroff(A_BOLD);

    int maxRows = LINES - 3;
    for (int i = 0; i < maxRows; i++) {
        int idx = scroll_offset_ + i;
        if (idx >= (int)procs.size()) break;

        mvprintw(i + 2, 0, "%-6d %-32s %6s %10d",
            procs[idx].get_pid(), procs[idx].get_name().c_str(),
            procs[idx].get_state().c_str(), procs[idx].get_virt_mem()
        );
    }

    refresh();
}