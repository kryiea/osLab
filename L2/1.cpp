#include <iostream>
#include <vector>
#include <algorithm>

struct Job {
    std::string name;
    int arrivalTime;
    int burstTime;
    int turnaroundTime;
    double weightTurnaroundTime;

    void calculateTurnaroundTime(int currentTime) {
        // 计算周转时间
        turnaroundTime = currentTime - arrivalTime;
    }

    void calculateWeightTurnaroundTime() {
        // 计算带权周转时间
        weightTurnaroundTime = static_cast<double>(turnaroundTime) / burstTime;
    }
};

void fcfs(std::vector<Job>& jobs) {
    int currentTime = 0;

    for (auto& job : jobs) {
        if (currentTime < job.arrivalTime) {
            currentTime = job.arrivalTime;
        }

        job.calculateTurnaroundTime(currentTime);
        job.calculateWeightTurnaroundTime();

        currentTime += job.burstTime;

        std::cout << "作业名称: " << job.name << "\n";
        std::cout << "周转时间: " << job.turnaroundTime << "\n";
        std::cout << "带权周转时间: " << job.weightTurnaroundTime << "\n";
        std::cout << "\n";
    }
}

void sjf(std::vector<Job>& jobs) {
    std::sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
        return a.burstTime < b.burstTime;
    });

    int currentTime = 0;

    for (auto& job : jobs) {
        if (currentTime < job.arrivalTime) {
            currentTime = job.arrivalTime;
        }

        job.calculateTurnaroundTime(currentTime);
        job.calculateWeightTurnaroundTime();

        currentTime += job.burstTime;

        std::cout << "作业名称: " << job.name << "\n";
        std::cout << "周转时间: " << job.turnaroundTime << "\n";
        std::cout << "带权周转时间: " << job.weightTurnaroundTime << "\n";
        std::cout << "\n";
    }
}

void hrn(std::vector<Job>& jobs) {
    int currentTime = 0;

    for (auto& job : jobs) {
        if (currentTime < job.arrivalTime) {
            currentTime = job.arrivalTime;
        }

        double responseRatio = static_cast<double>(job.burstTime + currentTime - job.arrivalTime) / job.burstTime;
        job.calculateTurnaroundTime(currentTime);
        job.calculateWeightTurnaroundTime();

        currentTime += job.burstTime;

        std::cout << "作业名称: " << job.name << "\n";
        std::cout << "周转时间: " << job.turnaroundTime << "\n";
        std::cout << "带权周转时间: " << job.weightTurnaroundTime << "\n";
        std::cout << "响应比: " << responseRatio << "\n";
        std::cout << "\n";
    }
}

int main() {
    std::vector<Job> jobs = {
        {"作业1", 0, 6},
        {"作业2", 1, 8},
        {"作业3", 2, 3},
        {"作业4", 3, 4},
        {"作业5", 4, 5},
        {"作业6", 0, 2},
        {"作业7", 1, 4},
        {"作业8", 2, 6},
        {"作业9", 3, 8},
        {"作业10", 4, 3}
    };

    std::cout << "先来先服务调度算法 (FCFS):\n";
    fcfs(jobs);
    std::cout << "---------------------------\n";

    std::cout << "最短作业优先调度算法 (SJF):\n";
    sjf(jobs);
    std::cout << "---------------------------\n";

    std::cout << "响应比高者优先调度算法 (HRN):\n";
    hrn(jobs);
    std::cout << "---------------------------\n";

    return 0;
}
