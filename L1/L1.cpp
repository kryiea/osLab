#include <iostream>
#include <time.h>
using namespace std;

// 3级就绪队列的时间片
int time_slice[4]{0, 1, 2, 3};
// 标记上次次运行的进程
PCB* last_run = nullptr;


// PCB
struct PCB{
    string name;    // 进程名字
    char state;     // R、W
    int runTime;    // 已运行时间
    int needTime;   // 需要运行时间
    int zTime;      // 周转时间
    int super;      // 优先级
    int acc_time;   // 累计运行时间
    int Q_level;    // 所在队列
    struct PCB* link;   // 下一个pcb
};

PCB* createPCB(int n); // 随机生成10个进程的就绪队列,不含头节点
void super_sort(PCB* head); // 优先级排序, 从大到小
void show(PCB* head);  // 打印就绪队列
void show_run(PCB* head);   // 打印当前运行的进程
int space(PCB* head);  // 就绪队列长度
PCB* destroy(PCB* head, PCB* p);   // 进程撤销，返回撤销后的就绪队列
void HPS(PCB* head);   // 最高优先数优先调度算法
void RR(PCB* head);   // 时间片轮转调度算法
PCB* head_to_tail(PCB* head);  //将头节点放到就绪队列尾部，返回新的头节点


// 手动创建一个进程
PCB* createPCB(){
    PCB* head = new PCB;

    head->state = 'W';
    head->runTime = 0;
    head->zTime = 0;
    head->acc_time = 0;
    head->link = nullptr;
    head->super = rand() % 10 + 1;

    // 输入进程名字
    cout << "请输入进程名字：" << endl;
    cin >> head->name;
    // 输入运行时间
    cout << "请输入进程需要运行时间：" << endl;
    cin >> head->needTime;

    cout << "进程" << head->name << "创建成功！" << endl;

    return head;
}



// 随机生成10个进程的就绪队列,不含头节点
// @param[in] n 进程个数
PCB* createPCB(int n){
    PCB* head = new PCB;
    PCB* p = head;
    p->name = "P" + to_string(1);
    p->state = 'W';
    p->runTime = 0;
    p->needTime = rand() % 10 + 1;
    p->zTime = 0;
    p->acc_time = 0;
    p->super = rand() % 10 + 1;
    p->link = nullptr;

    for(int i = 2; i <= n; i++){
        PCB* q = new PCB;
        q->name = "P" + to_string(i);
        q->state = 'W';
        q->runTime = 0;
        q->needTime = rand() % 10 + 1;
        q->zTime = 0;
        q->super = rand() % 10 + 1;
        q->link = nullptr;

        p->link = q;
        p = q;
    }
    return head;
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

// 打印就绪队列
void show(PCB* head){
    PCB* p = head;
    cout << "进程名\t状态\t已运行时间\t需要运行时间\t周转时间\t优先级" << endl;
    while(p != NULL){
        cout << p->name << "\t" << p->state << "\t" << p->runTime << "\t\t" << p->needTime << "\t\t" << p->zTime << "\t\t" << p->super << endl;
        p = p->link;
    }
    cout << "就绪队列长度：" << space(head) << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

// 打印当前运行的进程
void show_run(PCB* head){
    PCB* p = head;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "当前运行的进程："  << endl;
    cout << "进程名\t状态\t已运行时间\t需要运行时间\t周转时间\t优先级" << endl;
    if(p->state == 'R'){
        cout << p->name << "\t" << p->state << "\t" << p->runTime << "\t\t" << p->needTime << "\t\t" << p->zTime << "\t\t" << p->super << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << endl;

}

// 就绪队列长度
int space(PCB* head){
    PCB* p = head;
    int count = 0;
    while(p != NULL){
        count++;
        p = p->link;
    }
    return count;
}

// 进程撤销，返回撤销后的就绪队列
PCB* destroy(PCB* head, PCB* p){
    PCB* q = head;
    if(p == head){
        head = head->link;
        delete p;
        return head;
    }
    while(q->link != p){
        q = q->link;
    }
    q->link = p->link;
    delete p;
    return head;
}

// 最高优先数优先调度算法
void HPS(PCB* head){
    // 取出优先级最高的进程
    PCB* p = head;
    // 运行该进程
    p->state = 'R';
    p->runTime++;
    p->zTime++;
    // 优先级不小于1，每次运行优先级减1
    if(p->super > 1){
        p->super--;
    }
    // 打印当前运行的进程
    show_run(head);
}

// 时间片轮转调度算法
void RR(PCB* head){
    // 取出优先级最高的进程
    PCB* p = head;
    // 运行该进程
    p->state = 'R';
    p->runTime++;
    p->zTime++;
    // 打印当前运行的进程
    show_run(head);
}

//将头节点放到就绪队列尾部，返回新的头节点
PCB* head_to_tail(PCB* head){
    PCB* p = head;
    PCB* q = head->link;
    while(q->link != nullptr){
        q = q->link;
    }
    q->link = p;
    head = p->link;
    p->link = nullptr;
    return head;
}

// 加入就绪队列队尾
PCB* tail_to_tail(PCB* head, PCB* p){
    PCB* q = head;
    while(q->link != nullptr){
        q = q->link;
    }
    q->link = p;
    p->link = nullptr;
    return head;
}

// 多级反馈队列调度算法
void MFQ(PCB* Q[]){
    // Q[1] 是否有进程
    if(Q[1] != nullptr){
        // 取出优先级最高的进程
        PCB* p = Q[1];
        // 运行该进程
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        if(p->acc_time == time_slice[p->Q_level] && p->runTime != p->needTime){
            // 运行时间等于时间片，将该进程放到下一级就绪队尾
            p->Q_level++; 
            Q[p->Q_level] = tail_to_tail(Q[p->Q_level], p);
            p->acc_time = 0; // 累计运行时间清零
        }

        // 打印当前运行的进程
        show_run(p);
        p->runTime = 'W'; // 设置状态,等待下一次运行

        // 本次运行的进程
        last_run = p;

        // 是否摧毁进程
        if(p->runTime == p->needTime){
            // 打印提示
            last_run = nullptr; // 重置上次运行的进程
            cout << ">>>>>>>> 进程" << p->name << "已经运行完毕，撤销 <<<<<<<<" << endl << endl;
            Q[1] = destroy(Q[1], p);
        }

    }
    // Q[1] 为空，Q[2] 是否有进程
    else if(Q[2] != nullptr){
        // 取出优先级最高的进程
        PCB* p = Q[2];
        // 运行该进程
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        if(p->acc_time == time_slice[p->Q_level] && p->runTime != p->needTime){
            // 运行时间等于时间片，将该进程放到下一级就绪队尾
            p->Q_level++; 
            Q[p->Q_level] = tail_to_tail(Q[p->Q_level], p);
            p->acc_time = 0; // 累计运行时间清零
        }
        // 打印当前运行的进程
        show_run(p);
        p->runTime = 'W'; // 设置状态,等待下一次运行
    }
    // Q[1] Q[2] 都为空，Q[3] 是否有进程
    else if(Q[3] != nullptr){
        // 取出优先级最高的进程
        PCB* p = Q[3];
        // 运行该进程
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        // 打印当前运行的进程
        show_run(p);
        p->runTime = 'W'; // 设置状态,等待下一次运行
    }
    // Q[1] Q[2] Q[3] 都为空
    else{
        cout << "---- 进程已经全部完成----" << endl;
        exit(0);
    }
}

int main(){


    // 随机数种子
    srand((unsigned)time(NULL));

    cout << "------------------------------------------------------------------------" << endl;
    PCB* readyList = createPCB(10);
    super_sort(readyList);
    show(readyList);
    cout << "------------------------------------------------------------------------" << endl << endl;;
   
    cout << "--- 操作系统实验1 ---" << endl;
    cout << "1. 最高优先数优先调度算法" << endl;
    cout << "2. 时间片轮转调度算法" << endl;
    cout << "3. 多级反馈队列调度算法,抢占式" << endl;
    cout << "---------------------" << endl;

    cout << "请选择调度算法：" << endl;
    int select;
    cin >> select;
    cout << endl;
    
    switch(select){
        case 1:
            // 当前就绪队列长度
            int len;
            len = space(readyList);

            while (len != 0 && readyList != nullptr)
            {
                char ch = getchar();
                HPS(readyList);
                // 设置状态
                readyList->state = 'W';
                // 已经运行完的进程撤销
                if(readyList->runTime == readyList->needTime){
                    // 打印提示
                    cout << ">>>>>>>> 进程" << readyList->name << "已经运行完毕，撤销 <<<<<<<<" << endl << endl;
                    readyList = destroy(readyList, readyList);
                }
                if(len == 0 || readyList == nullptr){
                    cout << "---- 进程已经全部完成----" << endl;
                    exit(0);
                }
                super_sort(readyList);
                show(readyList);
                len = space(readyList);

                cout << "按任意键继续" << endl;
                ch = getchar();

            }
        case 2:
            // 周转时间
            int sum;
            sum = 0;
            // 当前就绪队列长度
            int len2;
            len2 = space(readyList);
            while(len2 != 0 && readyList != nullptr){
                char ch = getchar();
                RR(readyList);
                // 设置状态
                readyList->state = 'W';
                // 已经运行完的进程撤销
                cout << ">>>>>>>>平均周转时间：" << (float)sum/10 << endl << endl;
                if(readyList->runTime == readyList->needTime){
                    // 打印提示
                    cout << ">>>>>>>> 进程" << readyList->name << "已经运行完毕，撤销 <<<<<<<<" << endl << endl;
                    sum += readyList->zTime;
                    readyList = destroy(readyList, readyList);

                }
                len2 = space(readyList);
                if(len2 == 0 || readyList == nullptr){
                    cout << "平均周转时间：" << (float)sum/10 << endl;
                    cout << "---- 进程已经全部完成----" << endl;
                    exit(0);
                }               
                else{
                    // 运行后，将该进程放到队尾
                    readyList = head_to_tail(readyList);
                }
                show(readyList);
                cout << "按任意键继续" << endl;
                ch = getchar();
            }
            break;

        case 3:

            getchar();
            // 到达时间
            int time;
            time = 0;

            // 3级反馈队列 Q[1] Q[2] Q[3]
            PCB* Q[4];
            Q[1] = createPCB(1);
            Q[2] = createPCB(1);
            Q[3] = createPCB(1);

            // 当前就绪队列长度
            int Q1_len, Q2_len, Q3_len;
            Q1_len = space(Q[1]);
            Q2_len = space(Q[2]);
            Q3_len = space(Q[3]);

            // 输出就绪队列
            cout << "就绪队列1:" << endl; 
            show(Q[1]);
            cout << "就绪队列2:" << endl;
            show(Q[2]);
            cout << "就绪队列3:" << endl;
            show(Q[3]);
            



            // 3级就绪队列都不为空时
            while((Q1_len != 0 && Q2_len != 0 && Q3_len != 0 ) || (Q[1] != nullptr && Q[2] != nullptr && Q[3] != nullptr)){
                system("clear");

                // 是否要手动创建进程
                cout << "是否要创建新进程(Y/N)? " << endl;
                if(getchar() == 'Y'){
                    PCB* tmp = createPCB();
                    tmp->Q_level = 1;
                    // 加入Q[1] 队尾
                    Q[1] = tail_to_tail(Q[1], tmp);
                    cout << "到达时间：" << time << endl;
                    cout << "已经加入就绪队列1" << endl << endl;
                    Q1_len = space(Q[1]);
                    show(Q[1]);
                }


                // 调用多级反馈队列调度算法
                MFQ(Q);

                // 输出最新的就绪队列
                cout << "就绪队列1:" << endl;
                show(Q[1]);
                cout << "就绪队列2:" << endl;
                show(Q[2]);
                cout << "就绪队列3:" << endl;
                show(Q[3]);

                getchar();
                cout << "按任意键继续" << endl;
                time++; // 到达时间加1
                getchar();


                

            }
    

            break;
        default:
            cout << "输入错误！" << endl;
            break;
    }
    

    return 0;
}