/**
 * @file:		L1.cpp
 * @brief:		���̵���ʵ��L1
 * @author:		kryiea
 * @date:		2023/05/04 13:24:02
 */
#include <iostream>
#include <time.h>

using namespace std;

/**
 * @brief:	PCB��
 */
class PCB {
public:
    std::string name;        // ��������
    char state;         // R��W
    int runTime;        // ������ʱ��
    int needTime;       // ��Ҫ����ʱ��
    int zTime;          // ��תʱ��
    int super;          // ���ȼ�
    struct PCB* link;   // ��һ��pcb

public:

    // Ĭ�Ϲ���
    PCB(){};

    //���ι���
    PCB(std::string name, int i);

    // ���̳���
    void destroy();

    // ���д�PCB
    void running();

};

/**
 * @brief:	�������й�����	
 */
class pcbList{
public:
    PCB* h;
public:
    // Ĭ�Ϲ���
    pcbList(){};
    // ���ι��죬�������10�����̵ľ�������
    pcbList(PCB* head);

    // �������г���
    int space(PCB* head);

    // �������в鿴
    void show(PCB* head);

};


void PCB:: running(){
    this->runTime++;
    this->zTime++;
    this->state = 'W';
}

void PCB::destroy(){
    cout << "���̣�" << name <<  "�Ѿ����" << endl;
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
    cout << "���̺�No." << i << "�������" << endl;
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
        cout << "----��������----" << endl;
        cout << "qname \tstate \tsuper \tneedtime \truntime" << endl;
        while(tmp != nullptr){
            cout << tmp->name << "\t" << tmp->state << "\t" << tmp->super << "\t" << tmp->needTime << "\t\t" << tmp->runTime << endl;
            tmp = tmp->link;
        }
        cout << "---------------------------" << endl;
    }
    else if(head->state == 'R'){
        cout << "----��ǰ���н���----" << endl;
        cout << "qname \tstate \tsuper \tneedtime \truntime" << endl;
        cout << tmp->name << "\t" << tmp->state << "\t" << tmp->super << "\t" << tmp->needTime << "\t\t" << tmp->runTime << endl;
        cout << "---------------------------" << endl;
    }
}



// ��ǰ����PCB
PCB* runPtr;

// �˵�����
void menu(){
    //system("cls");
 
    // �����б�ready
    PCB* ready;
    // pcb�����б�L
    pcbList* L = new pcbList(ready); 

    L->show(L->h);
    

    cout << "1. ������������ȵ����㷨" << endl;
    cout << "2. ʱ��Ƭ��ת�����㷨" << endl;
    cout << "3. �༶�������е����㷨" << endl;
    cout << "��ѡ������㷨��";
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
            cout << "�����������" << endl;
            ch = getchar();
        }
        cout << "---- �����Ѿ�ȫ�����----" << endl;
    }

}

// ���ȼ�����, �Ӵ�С  
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

// ��������������㷨
void superFirst(PCB* ready){

    // ȡ�����ȼ���ߵĽ���
    PCB* p = ready;
    p->running();
    p->super--;
    p->state = 'W';
}

// ʱ��Ƭ��ת�㷨
void timeSlice(PCB* ready){
    PCB* p = ready;
    while(p != nullptr){
        p->running();
        p = p->link;
    }
}

// �༶�������е����㷨




int main(){
    //system("cls");
 
    // �����б� ready
    PCB* ready = nullptr;
    // pcb�����б�L
    pcbList* L = new pcbList(ready); 
    ready = L->h;
    super_sort(ready);
    L->h = ready;
    L->show(L->h);
    
    cout << "1. ������������ȵ����㷨" << endl;
    cout << "2. ʱ��Ƭ��ת�����㷨" << endl;
    cout << "3. �༶�������е����㷨" << endl;
    cout << "��ѡ������㷨��";
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
            
            cout << "�����������" << endl;
            ch = getchar();
        }
        cout << "---- �����Ѿ�ȫ�����----" << endl;
    }



    return 0;
}