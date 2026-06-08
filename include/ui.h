#include "process_info.h"

#include <ncurses.h>
#include <vector>

class NcursesRenderer {
public:
    void draw(std::vector<ProcessInfo>& procs);
    void handle_input(int proc_count);

private:
    int scroll_offset_ = 0;
};