#include "process_info.h"

#include <ncurses.h>
#include <vector>

class NcursesRenderer {
public:
    NcursesRenderer();
    
    void draw(std::vector<ProcessInfo>& procs);
    void handle_input(int proc_count);

    ~NcursesRenderer();

private:
    int scroll_offset_ = 0;
};