#include <iostream>

class pcbList;

/**
 * @brief:	PCB类	
 */
class PCB {
public:
    std::string name;        // 进程名字
    char state;         // R、W
    int runTime;        // 已运行时间
    int needTime;       // 需要运行时间
    int zTime;          // 周转时间
    int super;          // 优先级
    struct PCB* link;   // 下一个pcb

public:

    // 默认构造
    PCB(){};

    //带参构造
    PCB(std::string name, int i);

    // 进程撤销
    void destroy();

    // 运行此PCB
    void running();

};


/**
 * @brief:	就绪队列工具类	
 */
class pcbList{
public:
    PCB* head;
public:
    // 默认构造
    pcbList(){};
    // 带参构造，随机生成10个进程的就绪队列
    pcbList(PCB* head);

    // 就绪队列长度
    int space(PCB* head);

    // 就绪队列查看
    void show(PCB* head);

};