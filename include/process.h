#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class ProcessInfo {
public:
    ProcessInfo(int pid, std::string name, std::string state, 
        int virt_mem, float cpu_percent, float mem_percent);

    int get_pid() { return pid_; }
    std::string get_name() { return name_; }
    std::string get_state() { return state_; }
    int get_virt_mem() { return virt_mem_; }
    float get_cpu_percent() { return cpu_percent_; }
    float get_mem_percent() { return mem_percent_; } 
    
private:
    int pid_;
    std::string name_;
    std::string state_;
    int virt_mem_;
    float cpu_percent_;
    float mem_percent_;
};

class ProcessManager {
public:
    void update();
    std::vector<ProcessInfo>& get_processes() { return processes_; }

private:
    std::vector<ProcessInfo> readProcData();
    long get_total_cpu_time();
    long get_total_mem();

    std::unordered_map<int, long> prev_proc_times_;
    long prev_total_cpu_ = 0;

    std::vector<ProcessInfo> processes_;
};