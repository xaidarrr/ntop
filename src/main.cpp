#include "ui.h"
#include <unistd.h>

int main() {
    ProcessManager pm;
    NcursesRenderer* renderer = new NcursesRenderer();

    while(true) {
        pm.update();
        renderer->draw(pm.get_processes());
        sleep(3);
    }

    return 0;
}