#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

// ��������ṹ
struct Partition {
    int start;
    int size;
    string status;
    string process_id;
};

// ������з�������
vector<Partition> free_partitions;

// ��ʼ���ڴ�ռ�
void initializeMemory() {
    Partition os_partition = {0, 40, "ռ��", "OS"};
    Partition free_partition = {40, 600, "����", ""};
    free_partitions.push_back(free_partition);
}

// �״���Ӧ�㷨�����ڴ����
void firstFitAllocate(string process_id, int size) {
    bool allocated = false;

    for (int i = 0; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.size >= size) {
            if (partition.size == size) {
                partition.status = "ռ��";
                partition.process_id = process_id;
            } else {
                Partition new_partition = {partition.start, size, "ռ��", process_id};
                partition.start += size;
                partition.size -= size;
                free_partitions.insert(free_partitions.begin() + i, new_partition);
            }
            allocated = true;
            break;
        }
    }

    if (allocated) {
        cout << "�����ڴ������ " << process_id << " �ɹ�" << endl;
    } else {
        cout << "�޷������ڴ������ " << process_id << "���ڴ治��" << endl;
    }
}

// ѭ���״���Ӧ�㷨�����ڴ����
void nextFitAllocate(string process_id, int size) {
    bool allocated = false;
    int start_index = 0;

    for (int i = start_index; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.size >= size) {
            if (partition.size == size) {
                partition.status = "ռ��";
                partition.process_id = process_id;
            } else {
                Partition new_partition = {partition.start, size, "ռ��", process_id};
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
        cout << "�����ڴ������ " << process_id << " �ɹ�" << endl;
    } else {
        cout << "�޷������ڴ������ " << process_id << "���ڴ治��" << endl;
    }
}

// �����Ӧ�㷨�����ڴ����
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
            partition.status = "ռ��";
            partition.process_id = process_id;
        } else {
            Partition new_partition = {partition.start, size, "ռ��", process_id};
            partition.start += size;
            partition.size -= size;
            free_partitions.insert(free_partitions.begin() + best_index, new_partition);
        }
        allocated = true;
    }

    if (allocated) {
        cout << "�����ڴ������ " << process_id << " �ɹ�" << endl;
    } else {
        cout << "�޷������ڴ������ " << process_id << "���ڴ治��" << endl;
    }
}

// �����ڴ����
void deallocateMemory(string process_id) {
    bool deallocated = false;

    for (int i = 0; i < free_partitions.size(); i++) {
        Partition& partition = free_partitions[i];
        if (partition.process_id == process_id) {
            partition.status = "����";
            partition.process_id = "";
            deallocated = true;
            
            // �ϲ����ڵĿ��з���
            if (i > 0 && free_partitions[i-1].status == "����") {
                Partition& prev_partition = free_partitions[i-1];
                prev_partition.size += partition.size;
                free_partitions.erase(free_partitions.begin() + i);
                i--;
            }
            
            if (i < free_partitions.size() - 1 && free_partitions[i+1].status == "����") {
                Partition& next_partition = free_partitions[i+1];
                partition.size += next_partition.size;
                free_partitions.erase(free_partitions.begin() + i + 1);
            }
            
            break;
        }
    }

    if (deallocated) {
        cout << "���ս��� " << process_id << " ���ڴ�ɹ�" << endl;
    } else {
        cout << "δ�ҵ����� " << process_id << endl;
    }
}

// ��ʾ�����ڴ������
void displayFreePartitions() {
    cout << "-----------------------------------------" << endl;
    cout << "�����ڴ��������" << endl;
    cout << "-----------------------------------------" << endl;
    for (const Partition& partition : free_partitions) {
        cout << "��ʼ��ַ��" << partition.start << " | ��С��" << partition.size << " KB"
             << " | ״̬��" << partition.status << " | ����ID��" << partition.process_id << endl;
    }
    cout << "-----------------------------------------" << endl << endl;
}

int main() {
    int algorithm_choice;

    cout << "ѡ���㷨��" << endl;
    cout << "1. �״���Ӧ�㷨" << endl;
    cout << "2. ѭ���״���Ӧ�㷨" << endl;
    cout << "3. �����Ӧ�㷨" << endl;
    cout << "������ѡ��: ";
    cin >> algorithm_choice;

    // ��ʼ���ڴ�ռ�
    initializeMemory();

    // ��ҵ��������
    if (algorithm_choice == 1) {
        cout << "ѡ�����״���Ӧ�㷨" << endl;
        firstFitAllocate("��ҵ1", 130);
        displayFreePartitions();

        firstFitAllocate("��ҵ2", 60);
        displayFreePartitions();

        firstFitAllocate("��ҵ3", 100);
        displayFreePartitions();

        deallocateMemory("��ҵ2");
        displayFreePartitions();

        firstFitAllocate("��ҵ4", 200);
        displayFreePartitions();

        deallocateMemory("��ҵ3");
        displayFreePartitions();

        deallocateMemory("��ҵ1");
        displayFreePartitions();

        firstFitAllocate("��ҵ5", 140);
        displayFreePartitions();

        firstFitAllocate("��ҵ6", 60);
        displayFreePartitions();

        firstFitAllocate("��ҵ7", 50);
        displayFreePartitions();
    } else if (algorithm_choice == 2) {
        cout << "ѡ����ѭ���״���Ӧ�㷨" << endl;
        nextFitAllocate("��ҵ1", 130);
        displayFreePartitions();

        nextFitAllocate("��ҵ2", 60);
        displayFreePartitions();

        nextFitAllocate("��ҵ3", 100);
        displayFreePartitions();

        deallocateMemory("��ҵ2");
        displayFreePartitions();

        nextFitAllocate("��ҵ4", 200);
        displayFreePartitions();

        deallocateMemory("��ҵ3");
        displayFreePartitions();

        deallocateMemory("��ҵ1");
        displayFreePartitions();

        nextFitAllocate("��ҵ5", 140);
        displayFreePartitions();

        nextFitAllocate("��ҵ6", 60);
        displayFreePartitions();

        nextFitAllocate("��ҵ7", 50);
        displayFreePartitions();
    } else if (algorithm_choice == 3) {
        cout << "ѡ���������Ӧ�㷨" << endl;
        bestFitAllocate("��ҵ1", 130);
        displayFreePartitions();

        bestFitAllocate("��ҵ2", 60);
        displayFreePartitions();

        bestFitAllocate("��ҵ3", 100);
        displayFreePartitions();

        deallocateMemory("��ҵ2");
        displayFreePartitions();

        bestFitAllocate("��ҵ4", 200);
        displayFreePartitions();

        deallocateMemory("��ҵ3");
        displayFreePartitions();

        deallocateMemory("��ҵ1");
        displayFreePartitions();

        bestFitAllocate("��ҵ5", 140);
        displayFreePartitions();

        bestFitAllocate("��ҵ6", 60);
        displayFreePartitions();

        bestFitAllocate("��ҵ7", 50);
        displayFreePartitions();
    } else {
        cout << "��Ч��ѡ��" << endl;
    }

    return 0;
}
