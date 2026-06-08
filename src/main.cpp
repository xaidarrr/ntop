#include "ui.h"
#include "process_manager.h"

#include <unistd.h>

int main() {
    IProcessManager* pm = new ProcessManager();
    IRenderer* renderer = new NcursesRenderer();

    while(true) {
        pm->update();
        renderer->handle_input(pm->get_processes().size());
        renderer->draw(pm->get_processes());
        usleep(100000);
    }

    delete pm;
    delete renderer;

    return 0;
}