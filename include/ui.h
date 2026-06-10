#include "process_info.h"

#include <vector>

class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual void draw(std::vector<ProcessInfo>& procs) = 0;
    virtual void handle_input(int proc_count) = 0;
};

class NcursesRenderer final : public IRenderer {
public:
    void draw(std::vector<ProcessInfo>& procs) override;
    void handle_input(int proc_count) override;

private:
    int scroll_offset_ = 0;
};