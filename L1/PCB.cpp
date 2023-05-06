#include "PCB.hpp"
#include <iostream>

using namespace std;

void PCB:: running(){
    runTime++;
    zTime++;
    if(runTime >= needTime){
        this->destroy();
    }
    else{
        this->state = 'W';
    }
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
    this->head = head;
    PCB* head = new PCB(to_string(rand()%999), 1);
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
        cout << "qname \t state \t super \t needtime \t runtime" << endl;
        while(tmp != nullptr){
            cout << tmp->name << "\t" << tmp->state << "\t" << tmp->super << "\t" << tmp->needTime << tmp->runTime << endl;
            tmp = tmp->link;
        }
    }

}