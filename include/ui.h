#include "process_info.h"

#include <ncurses.h>
#include <vector>

class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual void draw(std::vector<ProcessInfo>& procs) = 0;
    virtual void handle_input(int proc_count) = 0;
};

class NcursesRenderer : public IRenderer {
public:
    NcursesRenderer();
    
    void draw(std::vector<ProcessInfo>& procs) override;
    void handle_input(int proc_count) override;

    ~NcursesRenderer() override;

private:
    int scroll_offset_ = 0;
};