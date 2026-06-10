#pragma once
#include "iprocess_manager.h"

#include <string>
#include <unordered_map>

class ProcessManager final : public IProcessManager {
public:
    ProcessManager() = default;

    void update() override;
    std::vector<ProcessInfo>& get_processes() override { return processes_; }

private:
    std::vector<ProcessInfo> readProcData();
    long get_total_cpu_time();
    unsigned int get_total_mem();

    std::unordered_map<int, long> prev_proc_times_;
    long prev_total_cpu_ = 0;

    std::vector<ProcessInfo> processes_;
};