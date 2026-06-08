#include "process_info.h"

ProcessInfo::ProcessInfo(int pid, const std::string& name, const std::string& state, 
        int virt_mem, float cpu_percent, float mem_percent) :
    pid_(pid), name_(name), state_(state), 
    virt_mem_(virt_mem), cpu_percent_(cpu_percent), mem_percent_(mem_percent) {}