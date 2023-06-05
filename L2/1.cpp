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
        // ������תʱ��
        turnaroundTime = currentTime - arrivalTime;
    }

    void calculateWeightTurnaroundTime() {
        // �����Ȩ��תʱ��
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

        std::cout << "��ҵ����: " << job.name << "\n";
        std::cout << "��תʱ��: " << job.turnaroundTime << "\n";
        std::cout << "��Ȩ��תʱ��: " << job.weightTurnaroundTime << "\n";
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

        std::cout << "��ҵ����: " << job.name << "\n";
        std::cout << "��תʱ��: " << job.turnaroundTime << "\n";
        std::cout << "��Ȩ��תʱ��: " << job.weightTurnaroundTime << "\n";
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

        std::cout << "��ҵ����: " << job.name << "\n";
        std::cout << "��תʱ��: " << job.turnaroundTime << "\n";
        std::cout << "��Ȩ��תʱ��: " << job.weightTurnaroundTime << "\n";
        std::cout << "��Ӧ��: " << responseRatio << "\n";
        std::cout << "\n";
    }
}

int main() {
    std::vector<Job> jobs = {
        {"��ҵ1", 0, 6},
        {"��ҵ2", 1, 8},
        {"��ҵ3", 2, 3},
        {"��ҵ4", 3, 4},
        {"��ҵ5", 4, 5},
        {"��ҵ6", 0, 2},
        {"��ҵ7", 1, 4},
        {"��ҵ8", 2, 6},
        {"��ҵ9", 3, 8},
        {"��ҵ10", 4, 3}
    };

    std::cout << "�����ȷ�������㷨 (FCFS):\n";
    fcfs(jobs);
    std::cout << "---------------------------\n";

    std::cout << "�����ҵ���ȵ����㷨 (SJF):\n";
    sjf(jobs);
    std::cout << "---------------------------\n";

    std::cout << "��Ӧ�ȸ������ȵ����㷨 (HRN):\n";
    hrn(jobs);
    std::cout << "---------------------------\n";

    return 0;
}
