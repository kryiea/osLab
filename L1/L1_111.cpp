/**
 * @file:		L1.cpp
 * @brief:		进程调度实验L1
 * @author:		kryiea
 * @date:		2023/05/04 13:24:02
 */
#include <iostream>
#include <time.h>

using namespace std;

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
    PCB* h;
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


void PCB:: running(){
    this->runTime++;
    this->zTime++;
    this->state = 'W';
}

void PCB::destroy(){
    cout << "进程：" << name <<  "已经完成" << endl;
    delete this;
}

PCB:: PCB(string name, int i){
    this->runTime = 0;
    this->state = 'W';
    this->link = nullptr;
    this->zTime = 0;
    this->name = name;
    this->super = rand()%6;
    this->needTime = rand()%10;
    cout << "进程号No." << i << "创建完成" << endl;
}

pcbList::pcbList(PCB* head){  
    head = new PCB(to_string(rand()%999), 1);
    this->h = head;

    PCB* cur = head;
    int num = 2;

    while(num < 11){
        PCB* tmp = new PCB(to_string(rand()%999), num);
        cur->link = tmp;
        cur = tmp;
        num++;
    }
}

int pcbList::space(PCB* head){
    int len = 0;
    PCB* pr = head;
    while(pr != nullptr){
        len++;
        pr = pr->link;
    }
    return len;
}

void pcbList::show(PCB* head){
    PCB* tmp = head;
    if(head->state == 'W'){
        cout << "----就绪队列----" << endl;
        cout << "qname \tstate \tsuper \tneedtime \truntime" << endl;
        while(tmp != nullptr){
            cout << tmp->name << "\t" << tmp->state << "\t" << tmp->super << "\t" << tmp->needTime << "\t\t" << tmp->runTime << endl;
            tmp = tmp->link;
        }
        cout << "---------------------------" << endl;
    }
    else if(head->state == 'R'){
        cout << "----当前运行进程----" << endl;
        cout << "qname \tstate \tsuper \tneedtime \truntime" << endl;
        cout << tmp->name << "\t" << tmp->state << "\t" << tmp->super << "\t" << tmp->needTime << "\t\t" << tmp->runTime << endl;
        cout << "---------------------------" << endl;
    }
}



// 当前运行PCB
PCB* runPtr;

// 菜单函数
void menu(){
    //system("cls");
 
    // 就绪列表ready
    PCB* ready;
    // pcb就绪列表L
    pcbList* L = new pcbList(ready); 

    L->show(L->h);
    

    cout << "1. 最高优先数优先调度算法" << endl;
    cout << "2. 时间片轮转调度算法" << endl;
    cout << "3. 多级反馈队列调度算法" << endl;
    cout << "请选择调度算法：";
    int select = 0;
    cin >> select;
    switch (select)
    {
    case 1:
        int len = L->space(ready);
        char ch;
        while(len != 0 && ready != nullptr){
            ch = getchar();
            runPtr = ready;
            ready = runPtr->link;
            runPtr->state = 'R';
            L->show(runPtr);
            L->show(L->h);
            runPtr->running();
            cout << "按任意键继续" << endl;
            ch = getchar();
        }
        cout << "---- 进程已经全部完成----" << endl;
    }

}

// 优先级排序, 从大到小  
void super_sort(PCB* head){
    PCB* p = head;
    PCB* q = head->link;
    PCB* tmp = new PCB();
    while(p->link != nullptr){
        while(q != nullptr){
            if(p->super < q->super){
                tmp->name = p->name;
                tmp->needTime = p->needTime;
                tmp->runTime = p->runTime;
                tmp->state = p->state;
                tmp->super = p->super;
                p->name = q->name;
                p->needTime = q->needTime;
                p->runTime = q->runTime;
                p->state = q->state;
                p->super = q->super;
                q->name = tmp->name;
                q->needTime = tmp->needTime;
                q->runTime = tmp->runTime;
                q->state = tmp->state;
                q->super = tmp->super;
            }
            q = q->link;
        }
        p = p->link;
        q = p->link;
    }
}

// 最高优先数优先算法
void superFirst(PCB* ready){

    // 取出优先级最高的进程
    PCB* p = ready;
    p->running();
    p->super--;
    p->state = 'W';
}

// 时间片轮转算法
void timeSlice(PCB* ready){
    PCB* p = ready;
    while(p != nullptr){
        p->running();
        p = p->link;
    }
}

// 多级反馈队列调度算法




int main(){
    //system("cls");
 
    // 就绪列表 ready
    PCB* ready = nullptr;
    // pcb就绪列表L
    pcbList* L = new pcbList(ready); 
    ready = L->h;
    super_sort(ready);
    L->h = ready;
    L->show(L->h);
    
    cout << "1. 最高优先数优先调度算法" << endl;
    cout << "2. 时间片轮转调度算法" << endl;
    cout << "3. 多级反馈队列调度算法" << endl;
    cout << "请选择调度算法：";
    int select = 0;
    cin >> select;
    switch (select)
    {
    case 1:
        int len = L->space(ready);
        char ch;
        while(len != 0 && ready != nullptr){
            ch = getchar();
            L->show(L->h);

            runPtr = ready;
            runPtr->state = 'R';
            L->show(runPtr);
            superFirst(runPtr);
            if(runPtr->needTime == runPtr->runTime){
                ready = runPtr->link;
                runPtr->destroy();
            }
            super_sort(ready);
            
            cout << "按任意键继续" << endl;
            ch = getchar();
        }
        cout << "---- 进程已经全部完成----" << endl;
    }



    return 0;
}