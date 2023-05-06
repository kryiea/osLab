#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 

#define getpch(type) (type*)malloc(sizeof(type)) 
#define NULL 0 

/* 定义进程控制块PCB */ 
struct pcb { 
    char name[10];  //进程名字
    char state;     //进程状态 
    int super;      //优先级
    int ntime;      //需要运行时间
    int rtime;      //已运行时间
    struct pcb* link; //next
}*ready=NULL,*p; 

typedef struct pcb PCB; 

/* 建立对进程进行优先级排列函数*/ 
void sort() { 
    PCB *first, *second; 
    int insert=0; 
    if((ready==NULL)||((p->super)>(ready->super))) /*优先级最大者,插入队首*/ 
    {
        p->link=ready; 
        ready=p; 
    } 
    else /* 进程比较优先级,插入适当的位置中*/ 
    { 
        first=ready; 
        second=first->link; 
        while(second!=NULL) 
        { 
            if((p->super)>(second->super)) /*若插入进程比当前进程优先数大,*/ 
            { /*插入到当前进程前面*/ 
                p->link=second; 
                first->link=p; 
                second=NULL; 
                insert=1; 
            } 
            else /* 插入进程优先数最低,则插入到队尾*/ 
            { 
                first=first->link; 
                second=second->link; 
            } 
        } 
        if(insert==0) first->link=p; 
    } 
} 

/* 建立进程控制块函数*/ 
void input() { 
    int i,num; 
    //clrscr(); /*清屏*/ 
    system("cls");
    printf("\n 请输入进程数量："); 
    scanf("%d",&num); 
    for(i=1;i<=num;i++) 
    { 
        printf("\n 进程号No.%d:\n",i); 
        p=getpch(PCB); 
        printf("\n 输入进程名:"); 
        scanf("%s",p->name); 
        printf("\n 输入进程优先数:"); 
        scanf("%d",&p->super); 
        printf("\n 输入进程运行时间:"); 
        scanf("%d",&p->ntime); 
        printf("\n"); 
        p->rtime=0;p->state='w'; 
        p->link=NULL; 
        sort(); /* 调用sort函数*/ 
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

/*建立进程显示函数,用于显示当前进程*/ 
void disp(PCB * pr) { 
    printf("\n qname \t state \t super \t ndtime \t runtime \n"); 
    printf("|%s\t",pr->name); 
    printf("|%c\t",pr->state); 
    printf("|%d\t",pr->super); 
    printf("|%d\t",pr->ntime); 
    printf("|%d\t",pr->rtime); 
    printf("\n"); 
} 

/* 建立进程查看函数 */ 
void check() { 
    PCB* pr; 
    printf("\n **** 当前正在运行的进程是:%s",p->name); /*显示当前运行进程*/ 
    disp(p); 
    pr=ready; 
    printf("\n ****当前就绪队列状态为:\n"); /*显示就绪队列状态*/ 
    while(pr!=NULL) 
    { 
        disp(pr); 
        pr=pr->link; 
    } 
} 



/*建立进程撤消函数(进程运行结束,撤消进程)*/ 
void destroy() { 
    printf("\n 进程 [%s] 已完成.\n",p->name); 
    free(p); 
} 


 /* 建立进程就绪函数(进程运行时间到,置就绪状态*/ 
void running(){ 
    (p->rtime)++; 
    if(p->rtime==p->ntime) 
        destroy(); /* 调用destroy函数*/ 
    else 
    { 
        (p->super)--; 
        p->state='w'; 
        sort(); /*调用sort函数*/ 
    } 
} 

/*主函数*/ 
int main() { 
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
        printf("\n 按任一键继续......"); 
        ch=getchar(); 
    } 
    printf("\n\n 进程已经完成.\n"); 
    ch=getchar(); 
} 