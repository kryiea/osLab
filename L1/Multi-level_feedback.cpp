#include <iostream>

using namespace std;

#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0

struct pcb{
    char name[10];      //进程名字
    char state;         //进程状态
    int ztime;          //周转时间
    int ntime;          //需要运行时间
    int rtime;          //已运行时间
    struct pcb* link;   //next
}*ready=NULL,*p, *last; //头节点和尾节点

typedef struct pcb PCB; 
int sum{}; // 总周转时间

void jump(){
    //空队列
    if(ready == NULL){
        ready = p;  
        last = p;    
    }
    else{
        //非空就绪队列
        last->link = p;
        last = p;
    }
}



/* 建立进程控制块函数*/ 
void input() { 
    int i,num; 
    system("cls");
    printf("\n 请输入进程数量："); 
    scanf("%d",&num); 
    for(i=1;i<=num;i++) 
    { 
        printf("\n 进程号No.%d:\n",i); 
        p=getpch(PCB); 
        printf("\n 输入进程??:"); 
        scanf("%s",p->name); 
        printf("\n 输入进程运行时间:"); 
        scanf("%d",&p->ntime); 
        printf("\n"); 
        p->rtime=0;
        p->state='w'; 
        p->link=nullptr; 
        p->ztime = 0;
        jump();

    } 
} 

/*建立进程显示函数,用于显示当前进程*/ 
void disp(PCB * pr) { 
    printf("\n qname \t state \t ndtime \t runtime \t ztime \n"); 
    printf("|%s\t",pr->name); 
    printf("|%c\t",pr->state); 
    printf("|%d\t",pr->ntime); 
    printf("|%d\t",pr->rtime); 
    printf("|%d\t",pr->ztime);
    printf("\n"); 
} 


/* 建立进程查看函数 */ 
void check() { 
    PCB* pr; 
    printf("\n **** 当前正在运行的进程是:%s",p->name); /*显示当前运行进程*/ 
    disp(p); 
    pr=ready; 
    printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状??*/ 
    while(pr!=NULL) 
    { 
        disp(pr); 
        pr=pr->link; 
    } 
} 

/*建立进程撤消函数(进程运行结束,撤消进程)*/ 
void destroy() { 
    printf("\n 进程 [%s] 已完成.\n",p->name); 
    sum += p->ztime;
    free(p); 
} 


 /* 建立进程就绪函数(进程运行时间??,置就绪状??*/ 
void running(){ 
    (p->rtime)++; 
    (p->ztime)++;
    if(p->rtime==p->ntime) 
    
        destroy(); /* 调用destroy函数*/ 
    else 
    { 
        p->state='w'; 
        jump();
    } 
} 

int space(){ 
    int l = 0; 
    PCB* pr=ready; 
    while(pr!=NULL) 
    { 
        l++; 
        pr=pr->link; 
    } 
    return(l); 
} 



int main(){

    int len,h=0; 
    char ch; 
    input(); 
    len=space(); 
    while((len!=0)&&(ready!=NULL)) 
    { 
        ch=getchar(); 
        h++; 
        printf("\n The execute number:%d \n",h); 
        p=ready; 
        ready=p->link; 
        p->link=NULL; 
        p->state='R'; 
        check(); 
        running(); 
        printf("\n 按任一键继续?......"); 
        ch=getchar(); 
    } 
    printf("\n\n 所有进程已经完成.\n"); 
    printf("\n\n 进程平均周转时间：%f",(float)sum/len);
    ch=getchar(); 
    return 0;
}