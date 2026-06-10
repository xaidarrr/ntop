#include "ui.h"
#include "process_manager.h"

#include <memory>
#include <unistd.h>

int main() {
    std::unique_ptr<IProcessManager> pm = std::make_unique<ProcessManager>();
    std::unique_ptr<IRenderer> renderer = std::make_unique<NcursesRenderer>();

    while(true) {
        pm->update();
        renderer->handle_input(pm->get_processes().size());
        renderer->draw(pm->get_processes());
        usleep(100000);
    }

    return 0;
}