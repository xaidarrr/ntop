#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <fstream>
#include "process.h"


ProcessInfo::ProcessInfo(int pid, std::string name, std::string state, 
        int virt_mem, float cpu_percent, float mem_percent) {
    pid_ = pid;
    name_ = name;
    state_ = state;
    virt_mem_ = virt_mem;
    cpu_percent_ = cpu_percent;
    mem_percent_ = mem_percent;
}

void ProcessManager::update() {
    processes_.clear();
    processes_ = readProcData();
}

long ProcessManager::get_total_cpu_time() {
    std::ifstream cpu_data("/proc/stat");
    std::string label;
    long user, nice, system, idle, iowait, irq, softirq;
    cpu_data >> label >> user >> nice >> system >> idle >> iowait >> irq >> softirq;
    return user + nice + system + idle + iowait + irq + softirq;
}

long ProcessManager::get_total_mem() {
    std::ifstream mem_data("/proc/meminfo");
    std::string label, unit;
    long total;
    mem_data >> label >> total >> unit;
    return total;
}

std::vector<ProcessInfo> ProcessManager::readProcData() {
    std::vector<ProcessInfo> processes;

    long total_cpu = get_total_cpu_time();
    long total_mem = get_total_mem();
    long cpu_delta = total_cpu - prev_total_cpu_;
    prev_total_cpu_ = total_cpu;

    std::unordered_map<int, long> cur_proc_times;

    for (auto& entry : std::filesystem::directory_iterator("/proc")) {
        std::string proc_dir_name = entry.path().filename();

        if (!std::all_of(proc_dir_name.begin(), proc_dir_name.end(), [](unsigned char c) { return std::isdigit(c); })) {
            continue;
        }

        std::ifstream proc_data("/proc/" + proc_dir_name + "/status");
        if (!proc_data) continue;

        int pid = std::stoi(proc_dir_name);
        std::string line;
        std::string proc_name = "";
        std::string proc_state = "";
        int virt_mem = 0, virt_rss = 0;

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
            }
            if (line.find("VmRSS:") == 0) {
                std::stringstream ss(line);
                std::string label, unit;

                ss >> label >> virt_rss >> unit;
            }
        }

        std::ifstream stat("/proc/" + proc_dir_name + "/stat");
        if (!stat) continue;
        long proc_time = 0;
        long utime = 0, stime = 0;
        std::string temp;

        stat >> temp >> temp >>  temp >> temp >>  temp >> temp
             >> temp >> temp >>  temp >> temp >>  temp >> temp >> temp
             >> utime >> stime;

        proc_time = utime + stime;
        cur_proc_times[pid] = proc_time;

        float cpu_percent = 0.0f;
        if (cpu_delta > 0) {
            long proc_delta = proc_time - prev_proc_times_[pid];
            cpu_percent = 100.0f * proc_delta / cpu_delta;
        }

        float mem_percent = (total_mem > 0)
            ? 100.0f * virt_rss / total_mem
            : 0.0f;

        processes.emplace_back(pid, proc_name, proc_state, virt_mem, cpu_percent, mem_percent);
    }

    prev_proc_times_ = cur_proc_times;

    std::sort(processes.begin(), processes.end(), [](ProcessInfo& a, ProcessInfo& b) {
        return a.get_cpu_percent() > b.get_cpu_percent();
    });

    return processes;
}