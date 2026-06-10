#include "irenderer.h"

class NcursesRenderer final : public IRenderer {
public:
    NcursesRenderer();
    ~NcursesRenderer() override;

    void draw(std::vector<ProcessInfo>& procs) override;
    void handle_input(int proc_count) override;

private:
    int scroll_offset_ = 0;
};