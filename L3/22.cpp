#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// 定义分区结构
struct Partition {
    int start;
    int size;
    string status;
    string process_id;
};

// 定义空闲分区链表
vector<Partition> free_partitions;

// 初始化内存空间
void initializeMemory() {
    Partition os_partition = {0, 40, "占用", "OS"};
    Partition free_partition = {40, 600, "空闲", ""};
    free_partitions.push_back(free_partition);
}

// 首次适应算法分配内存分区
void firstFitAllocate(string process_id, int size) {
    bool allocated = false;

    for (int i = 0; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.size >= size) {
            if (partition.size == size) {
                partition.status = "占用";
                partition.process_id = process_id;
            } else {
                Partition new_partition = {partition.start, size, "占用", process_id};
                partition.start += size;
                partition.size -= size;
                free_partitions.insert(free_partitions.begin() + i, new_partition);
            }
            allocated = true;
            break;
        }
    }

    if (allocated) {
        cout << "分配内存给进程 " << process_id << " 成功" << endl;
    } else {
        cout << "无法分配内存给进程 " << process_id << "，内存不足" << endl;
    }
}

// 循环首次适应算法分配内存分区
void nextFitAllocate(string process_id, int size) {
    bool allocated = false;
    int start_index = 0;

    for (int i = start_index; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.size >= size) {
            if (partition.size == size) {
                partition.status = "占用";
                partition.process_id = process_id;
            } else {
                Partition new_partition = {partition.start, size, "占用", process_id};
                partition.start += size;
                partition.size -= size;
                free_partitions.insert(free_partitions.begin() + i, new_partition);
            }
            allocated = true;
            start_index = i;
            break;
        }
    }

    if (allocated) {
        cout << "分配内存给进程 " << process_id << " 成功" << endl;
    } else {
        cout << "无法分配内存给进程 " << process_id << "，内存不足" << endl;
    }
}

// 最佳适应算法分配内存分区
void bestFitAllocate(string process_id, int size) {
    bool allocated = false;
    int best_index = -1;
    int min_size = INT_MAX;

    for (int i = 0; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.size >= size && partition.size < min_size) {
            best_index = i;
            min_size = partition.size;
        }
    }

    if (best_index != -1) {
        Partition& partition = free_partitions[best_index];
        if (partition.size == size) {
            partition.status = "占用";
            partition.process_id = process_id;
        } else {
            Partition new_partition = {partition.start, size, "占用", process_id};
            partition.start += size;
            partition.size -= size;
            free_partitions.insert(free_partitions.begin() + best_index, new_partition);
        }
        allocated = true;
    }

    if (allocated) {
        cout << "分配内存给进程 " << process_id << " 成功" << endl;
    } else {
        cout << "无法分配内存给进程 " << process_id << "，内存不足" << endl;
    }
}

// 回收内存分区
void deallocateMemory(string process_id) {
    bool deallocated = false;

    for (int i = 0; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.process_id == process_id) {
            partition.status = "空闲";
            partition.process_id = "";
            deallocated = true;
            
            // 合并相邻的空闲分区
            if (i > 0 && free_partitions[i-1].status == "空闲") {
                Partition& prev_partition = free_partitions[i-1];
                prev_partition.size += partition.size;
                free_partitions.erase(free_partitions.begin() + i);
                i--;
            }
            
            if (i < free_partitions.size() - 1 && free_partitions[i+1].status == "空闲") {
                Partition& next_partition = free_partitions[i+1];
                partition.size += next_partition.size;
                free_partitions.erase(free_partitions.begin() + i + 1);
            }
            
            break;
        }
    }

    if (deallocated) {
        cout << "回收进程 " << process_id << " 的内存成功" << endl;
    } else {
        cout << "未找到进程 " << process_id << endl;
    }
}

// 显示空闲内存分区链
void displayFreePartitions() {
    cout << "-----------------------------------------" << endl;
    cout << "空闲内存分区链：" << endl;
    cout << "-----------------------------------------" << endl;
    for (const Partition& partition : free_partitions) {
        cout << "起始地址：" << partition.start << " | 大小：" << partition.size << " KB"
             << " | 状态：" << partition.status << " | 进程ID：" << partition.process_id << endl;
    }
    cout << "-----------------------------------------" << endl << endl;
}

int main() {
    int algorithm_choice;

    cout << "选择算法：" << endl;
    cout << "1. 首次适应算法" << endl;
    cout << "2. 循环首次适应算法" << endl;
    cout << "3. 最佳适应算法" << endl;
    cout << "请输入选项: ";
    cin >> algorithm_choice;

    // 初始化内存空间
    initializeMemory();

    // 作业请求序列
    if (algorithm_choice == 1) {
        cout << "选择了首次适应算法" << endl;
        firstFitAllocate("作业1", 130);
        displayFreePartitions();

        firstFitAllocate("作业2", 60);
        displayFreePartitions();

        firstFitAllocate("作业3", 100);
        displayFreePartitions();

        deallocateMemory("作业2");
        displayFreePartitions();

        firstFitAllocate("作业4", 200);
        displayFreePartitions();

        deallocateMemory("作业3");
        displayFreePartitions();

        deallocateMemory("作业1");
        displayFreePartitions();

        firstFitAllocate("作业5", 140);
        displayFreePartitions();

        firstFitAllocate("作业6", 60);
        displayFreePartitions();

        firstFitAllocate("作业7", 50);
        displayFreePartitions();
    } else if (algorithm_choice == 2) {
        cout << "选择了循环首次适应算法" << endl;
        nextFitAllocate("作业1", 130);
        displayFreePartitions();

        nextFitAllocate("作业2", 60);
        displayFreePartitions();

        nextFitAllocate("作业3", 100);
        displayFreePartitions();

        deallocateMemory("作业2");
        displayFreePartitions();

        nextFitAllocate("作业4", 200);
        displayFreePartitions();

        deallocateMemory("作业3");
        displayFreePartitions();

        deallocateMemory("作业1");
        displayFreePartitions();

        nextFitAllocate("作业5", 140);
        displayFreePartitions();

        nextFitAllocate("作业6", 60);
        displayFreePartitions();

        nextFitAllocate("作业7", 50);
        displayFreePartitions();
    } else if (algorithm_choice == 3) {
        cout << "选择了最佳适应算法" << endl;
        bestFitAllocate("作业1", 130);
        displayFreePartitions();

        bestFitAllocate("作业2", 60);
        displayFreePartitions();

        bestFitAllocate("作业3", 100);
        displayFreePartitions();

        deallocateMemory("作业2");
        displayFreePartitions();

        bestFitAllocate("作业4", 200);
        displayFreePartitions();

        deallocateMemory("作业3");
        displayFreePartitions();

        deallocateMemory("作业1");
        displayFreePartitions();

        bestFitAllocate("作业5", 140);
        displayFreePartitions();

        bestFitAllocate("作业6", 60);
        displayFreePartitions();

        bestFitAllocate("作业7", 50);
        displayFreePartitions();
    } else {
        cout << "无效的选择" << endl;
    }

    return 0;
}
