#include "ui.h"

void NcursesRenderer::draw(std::vector<ProcessInfo>& procs) {
    clear();
    attron(A_BOLD);
    mvprintw(0, 0, "%-6s %-32s %10s %12s", "PID", "NAME", "STATE", "MEM (MB)");
    attroff(A_BOLD);

    int maxRows = LINES - 3;
    for (int i = 0; i < (int)procs.size() && i < maxRows; i++) {
        mvprintw(i + 2, 0, "%-6d %-32s %6s %10d",
            procs[i].get_pid(), procs[i].get_name().c_str(),
            procs[i].get_state().c_str(), procs[i].get_virt_mem()
        );
    }

    refresh();
}