#pragma once
#include "process_info.h"

#include <vector>

class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual void draw(std::vector<ProcessInfo>& procs) = 0;
    virtual void handle_input(int proc_count) = 0;
};