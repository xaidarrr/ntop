#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>

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

class ProcessManager {
public:
    void update();
    std::vector<ProcessInfo>& get_processes() { return processes_; }

private:
    std::vector<ProcessInfo> readProcData();
    std::vector<ProcessInfo> processes_;
};

void ProcessManager::update() {
    processes_.clear();
    processes_ = readProcData();
}

std::vector<ProcessInfo> ProcessManager::readProcData() {
    std::vector<ProcessInfo> processes;

    for (auto& entry : std::filesystem::directory_iterator("/proc")) {
        std::string proc_dir_name = entry.path().filename();

        if (!std::all_of(proc_dir_name.begin(), proc_dir_name.end(), [](unsigned char c) { return std::isdigit(c); })) {
            continue;
        }

        std::ifstream proc_data("/proc/" + proc_dir_name + "/status");

        int pid = std::stoi(proc_dir_name);
        std::string line;
        std::string proc_name;
        std::string proc_state;
        unsigned long virt_mem;

        while (std::getline(proc_data, line)) {
            if (line.find("Name:") == 0) {
                std::stringstream ss(line);
                std::string label;

                ss >> label;
                std::getline(ss >> std::ws, proc_name);
            }

            if (line.find("State:") == 0) {
                std::stringstream ss(line);
                std::string label;

                ss >> label >> proc_state;
            }

            if (line.find("VmSize:") == 0) {
                std::stringstream ss(line);
                std::string label, unit;

                ss >> label >> virt_mem >> unit;
                virt_mem /= 1024;
                break;
            }
        }

        processes.emplace_back(pid, proc_name, proc_state, virt_mem);
    }

    return processes;
}