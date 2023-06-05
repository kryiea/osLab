#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <iomanip>

// 进程控制块（PCB）结构体
struct ProcessControlBlock {
    std::string processName;
    int priority;   // 优先级
    int arrivalTime;// 到达时间
    int remainingTime; // 剩余执行时间
    int usedCPUTime;    // 已经使用的CPU时间
    std::string processStatus; // 进程状态

    // 构造函数
    ProcessControlBlock(std::string name, int pri, int arrival, int time)
        : processName(std::move(name)), priority(pri), arrivalTime(arrival),
          remainingTime(time), usedCPUTime(0), processStatus("Ready") {}
};

// 多级反馈队列调度程序类
class MFQS_Scheduler {
private:
    std::vector<std::queue<ProcessControlBlock>> feedbackQueues;
    std::vector<std::string> feedbackQueueNames;
    int timeSlice;

public:
    MFQS_Scheduler(int slice, const std::vector<std::string>& queueNames)
        : feedbackQueues(queueNames.size()), feedbackQueueNames(queueNames), timeSlice(slice) {}

    void addProcess(const ProcessControlBlock& process) {
        feedbackQueues[0].push(process); // 将新进程放入第一级队列
    }

    void run() {
        int currentQueue = 0;

        while (true) {
            bool allQueuesEmpty = true;

            // 检查当前队列是否有进程需要执行 
            if (!feedbackQueues[currentQueue].empty()) {
                ProcessControlBlock currentProcess = feedbackQueues[currentQueue].front();
                feedbackQueues[currentQueue].pop();
                currentProcess.processStatus = "Running";

                int remainingTime = currentProcess.remainingTime;

                if (remainingTime > timeSlice) {
                    currentProcess.usedCPUTime += timeSlice;
                    currentProcess.remainingTime -= timeSlice;
                    feedbackQueues[currentQueue + 1].push(currentProcess); // 将进程转移到下一级队列
                } else {
                    currentProcess.usedCPUTime += remainingTime;
                    currentProcess.remainingTime = 0;
                }

                std::cout << "Running process: " << currentProcess.processName << std::endl;
                printQueueStatus();
                std::cout << "------------------------------------" << std::endl;

                if (currentProcess.remainingTime > 0) {
                    currentProcess.processStatus = "Ready";
                    feedbackQueues[currentQueue].push(currentProcess); // 将进程重新放回当前队列
                } else {
                    currentProcess.processStatus = "Finished";
                    std::cout << "Process " << currentProcess.processName << " finished." << std::endl;
                }

                allQueuesEmpty = false;  // 当前队列有进程执行
            }

            // 检查后续队列是否还有进程
            for (int i = currentQueue + 1; i < feedbackQueues.size(); ++i) {
                if (!feedbackQueues[i].empty()) {
                    allQueuesEmpty = false;
                    break;
                }
            }

            if (allQueuesEmpty) {
                // 所有队列都为空，检查第一级队列是否有进程，如果没有则退出循环
                if (feedbackQueues[0].empty()) {
                    break;
                }
            }

            currentQueue = (currentQueue + 1) % feedbackQueues.size(); // 切换到下一个队列
        }
    }

    // 打印队列的状态，按照队列的优先级从高到低打印，表格形式
    void printQueueStatus() {
        std::cout << "Queue Status:" << std::endl;
        std::cout << std::setw(15) << "Process Name" << std::setw(15) << "Priority"
                  << std::setw(15) << "Arrival Time" << std::setw(15) << "Remaining Time"
                  << std::setw(15) << "Used CPU Time" << std::setw(15) << "Status" << std::endl;

        for (int i = feedbackQueues.size() - 1; i >= 0; --i) {
            std::queue<ProcessControlBlock> queue = feedbackQueues[i];
            std::cout << "Queue " << i << ": " << feedbackQueueNames[i] << std::endl;

            while (!queue.empty()) {
                ProcessControlBlock process = queue.front();
                queue.pop();
                std::cout << std::setw(15) << process.processName << std::setw(15) << process.priority
                          << std::setw(15) << process.arrivalTime << std::setw(15) << process.remainingTime
                          << std::setw(15) << process.usedCPUTime << std::setw(15) << process.processStatus << std::endl;
            }
        }
    }
};

int main() {
    // 创建多级反馈队列调度程序对象
    std::vector<std::string> queueNames = {"Queue 0", "Queue 1", "Queue 2"};
    MFQS_Scheduler scheduler(4, queueNames); // 时间片为5，三个级别的队列

    // 添加进程到调度程序
    scheduler.addProcess(ProcessControlBlock("Process A", 2, 0, 15));
    scheduler.addProcess(ProcessControlBlock("Process B", 0, 2, 10));
    scheduler.addProcess(ProcessControlBlock("Process C", 3, 4, 8));
    scheduler.addProcess(ProcessControlBlock("Process D", 2, 6, 12));
    scheduler.addProcess(ProcessControlBlock("Process E", 1, 8, 6));
    scheduler.addProcess(ProcessControlBlock("Process F", 0, 10, 9));


    // 运行进程调度程序
    scheduler.run();

    return 0;
}

