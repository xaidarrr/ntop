#include <string>

class ProcessInfo {
public:
    ProcessInfo(int pid, std::string name, std::string state, int virt_mem) {
        pid_ = pid;
        name_ = name;
        state_ = state;
        virt_mem_ = virt_mem;
    }

    int get_pid() { return pid_; }
    std::string get_name() { return name_; }
    std::string get_state() { return state_; }
    int get_virt_mem() { return virt_mem_; }
    
private:
    int pid_;
    std::string name_;
    std::string state_;
    int virt_mem_;
};