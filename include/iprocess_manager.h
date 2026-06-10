#include "process_info.h"

#include <vector>

class IProcessManager {
public:
    virtual ~IProcessManager() = default;

    virtual void update() = 0; 
    virtual std::vector<ProcessInfo>& get_processes() = 0;
};