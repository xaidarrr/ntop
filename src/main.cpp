#include "ui.h"
#include <unistd.h>

int main() {
    ProcessManager pm;
    NcursesRenderer renderer = NcursesRenderer();

    while(true) {
        pm.update();
        renderer.handle_input(pm.get_processes().size());
        renderer.draw(pm.get_processes());
        usleep(100000);
    }

    return 0;
}