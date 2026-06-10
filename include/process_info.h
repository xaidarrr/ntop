#pragma once
#include <string>

struct ProcessInfo final {
public:
    ProcessInfo() = delete;

    ProcessInfo(int pid, const std::string& name, const std::string& state, 
        int virt_mem, float cpu_percent, float mem_percent) :
    pid_{pid}, name_{name}, state_{state}, 
    virt_mem_{virt_mem}, cpu_percent_{cpu_percent}, mem_percent_{mem_percent} {}

    int get_pid() const { return pid_; }
    std::string get_name() const { return name_; }
    std::string get_state() const { return state_; }
    int get_virt_mem() const { return virt_mem_; }
    float get_cpu_percent() const { return cpu_percent_; }
    float get_mem_percent() const { return mem_percent_; } 
    
private:
    int pid_;
    std::string name_;
    std::string state_;
    int virt_mem_;
    float cpu_percent_;
    float mem_percent_;
};