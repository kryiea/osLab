#include <iostream>

using namespace std;

#define getpch(type) (type*)malloc(sizeof(type)) 

struct pcb{
    char name[10];      //????????
    char state;         //??????
    int ztime;          //??????
    int ntime;          //??????????
    int rtime;          //?????????
    struct pcb* link;   //next
}*ready=NULL,*p, *last; //??????????

typedef struct pcb PCB; 
int sum{}; // ????????

void jump(){
    //?????
    if(ready == NULL){
        ready = p;  
        last = p;    
    }
    else{
        //??????????
        last->link = p;
        last = p;
    }
}



/* ????????????D??*/ 
void input() { 
    int i,num; 
    system("cls");
    printf("\n ???????????????"); 
    scanf("%d",&num); 
    for(i=1;i<=num;i++) 
    { 
        printf("\n ?????No.%d:\n",i); 
        p=getpch(PCB); 
        printf("\n ?????????:"); 
        scanf("%s",p->name); 
        printf("\n ??????????????:"); 
        scanf("%d",&p->ntime); 
        printf("\n"); 
        p->rtime=0;
        p->state='w'; 
        p->link=nullptr; 
        p->ztime = 0;
        jump();

    } 
} 

/*???????????????,??????????????*/ 
void disp(PCB * pr) { 
    printf("\n qname \t state \t ndtime \t runtime \t ztime \n"); 
    printf("|%s\t",pr->name); 
    printf("|%c\t",pr->state); 
    printf("|%d\t",pr->ntime); 
    printf("|%d\t",pr->rtime); 
    printf("|%d\t",pr->ztime);
    printf("\n"); 
} 


/* ????????????? */ 
void check() { 
    PCB* pr; 
    printf("\n **** ??????????????????:%s",p->name); /*??????????????*/ 
    disp(p); 
    pr=ready; 
    printf("\n ****??????????????:\n"); /*??????????????*/ 
    while(pr!=NULL) 
    { 
        disp(pr); 
        pr=pr->link; 
    } 
} 

/*???????????????(????????????,????????)*/ 
void destroy() { 
    printf("\n ???? [%s] ?????.\n",p->name); 
    sum += p->ztime;
    free(p); 
} 


 /* ???????????????(?????????????,????????*/ 
void running(){ 
    (p->rtime)++; 
    (p->ztime)++;
    if(p->rtime==p->ntime) 

        destroy(); /* ????destroy????*/ 
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
        printf("\n ????????????......"); 
        ch=getchar(); 
    } 
    printf("\n\n ??????????????.\n"); 
    printf("\n\n ?????????????%f",(float)sum/len);
    ch=getchar(); 
    return 0;
}