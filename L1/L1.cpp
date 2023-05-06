#include <iostream>
#include <time.h>
using namespace std;

// 3���������е�ʱ��Ƭ
int time_slice[4]{0, 1, 2, 3};
// ����ϴδ����еĽ���
PCB* last_run = nullptr;


// PCB
struct PCB{
    string name;    // ��������
    char state;     // R��W
    int runTime;    // ������ʱ��
    int needTime;   // ��Ҫ����ʱ��
    int zTime;      // ��תʱ��
    int super;      // ���ȼ�
    int acc_time;   // �ۼ�����ʱ��
    int Q_level;    // ���ڶ���
    struct PCB* link;   // ��һ��pcb
};

PCB* createPCB(int n); // �������10�����̵ľ�������,����ͷ�ڵ�
void super_sort(PCB* head); // ���ȼ�����, �Ӵ�С
void show(PCB* head);  // ��ӡ��������
void show_run(PCB* head);   // ��ӡ��ǰ���еĽ���
int space(PCB* head);  // �������г���
PCB* destroy(PCB* head, PCB* p);   // ���̳��������س�����ľ�������
void HPS(PCB* head);   // ������������ȵ����㷨
void RR(PCB* head);   // ʱ��Ƭ��ת�����㷨
PCB* head_to_tail(PCB* head);  //��ͷ�ڵ�ŵ���������β���������µ�ͷ�ڵ�


// �ֶ�����һ������
PCB* createPCB(){
    PCB* head = new PCB;

    head->state = 'W';
    head->runTime = 0;
    head->zTime = 0;
    head->acc_time = 0;
    head->link = nullptr;
    head->super = rand() % 10 + 1;

    // �����������
    cout << "������������֣�" << endl;
    cin >> head->name;
    // ��������ʱ��
    cout << "�����������Ҫ����ʱ�䣺" << endl;
    cin >> head->needTime;

    cout << "����" << head->name << "�����ɹ���" << endl;

    return head;
}



// �������10�����̵ľ�������,����ͷ�ڵ�
// @param[in] n ���̸���
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

// ��ӡ��������
void show(PCB* head){
    PCB* p = head;
    cout << "������\t״̬\t������ʱ��\t��Ҫ����ʱ��\t��תʱ��\t���ȼ�" << endl;
    while(p != NULL){
        cout << p->name << "\t" << p->state << "\t" << p->runTime << "\t\t" << p->needTime << "\t\t" << p->zTime << "\t\t" << p->super << endl;
        p = p->link;
    }
    cout << "�������г��ȣ�" << space(head) << endl;
    cout << "--------------------------------------------------------------------" << endl;
}

// ��ӡ��ǰ���еĽ���
void show_run(PCB* head){
    PCB* p = head;
    cout << "--------------------------------------------------------------------" << endl;
    cout << "��ǰ���еĽ��̣�"  << endl;
    cout << "������\t״̬\t������ʱ��\t��Ҫ����ʱ��\t��תʱ��\t���ȼ�" << endl;
    if(p->state == 'R'){
        cout << p->name << "\t" << p->state << "\t" << p->runTime << "\t\t" << p->needTime << "\t\t" << p->zTime << "\t\t" << p->super << endl;
    }
    cout << "--------------------------------------------------------------------" << endl;
    cout << endl;

}

// �������г���
int space(PCB* head){
    PCB* p = head;
    int count = 0;
    while(p != NULL){
        count++;
        p = p->link;
    }
    return count;
}

// ���̳��������س�����ľ�������
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

// ������������ȵ����㷨
void HPS(PCB* head){
    // ȡ�����ȼ���ߵĽ���
    PCB* p = head;
    // ���иý���
    p->state = 'R';
    p->runTime++;
    p->zTime++;
    // ���ȼ���С��1��ÿ���������ȼ���1
    if(p->super > 1){
        p->super--;
    }
    // ��ӡ��ǰ���еĽ���
    show_run(head);
}

// ʱ��Ƭ��ת�����㷨
void RR(PCB* head){
    // ȡ�����ȼ���ߵĽ���
    PCB* p = head;
    // ���иý���
    p->state = 'R';
    p->runTime++;
    p->zTime++;
    // ��ӡ��ǰ���еĽ���
    show_run(head);
}

//��ͷ�ڵ�ŵ���������β���������µ�ͷ�ڵ�
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

// ����������ж�β
PCB* tail_to_tail(PCB* head, PCB* p){
    PCB* q = head;
    while(q->link != nullptr){
        q = q->link;
    }
    q->link = p;
    p->link = nullptr;
    return head;
}

// �༶�������е����㷨
void MFQ(PCB* Q[]){
    // Q[1] �Ƿ��н���
    if(Q[1] != nullptr){
        // ȡ�����ȼ���ߵĽ���
        PCB* p = Q[1];
        // ���иý���
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        if(p->acc_time == time_slice[p->Q_level] && p->runTime != p->needTime){
            // ����ʱ�����ʱ��Ƭ�����ý��̷ŵ���һ��������β
            p->Q_level++; 
            Q[p->Q_level] = tail_to_tail(Q[p->Q_level], p);
            p->acc_time = 0; // �ۼ�����ʱ������
        }

        // ��ӡ��ǰ���еĽ���
        show_run(p);
        p->runTime = 'W'; // ����״̬,�ȴ���һ������

        // �������еĽ���
        last_run = p;

        // �Ƿ�ݻٽ���
        if(p->runTime == p->needTime){
            // ��ӡ��ʾ
            last_run = nullptr; // �����ϴ����еĽ���
            cout << ">>>>>>>> ����" << p->name << "�Ѿ�������ϣ����� <<<<<<<<" << endl << endl;
            Q[1] = destroy(Q[1], p);
        }

    }
    // Q[1] Ϊ�գ�Q[2] �Ƿ��н���
    else if(Q[2] != nullptr){
        // ȡ�����ȼ���ߵĽ���
        PCB* p = Q[2];
        // ���иý���
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        if(p->acc_time == time_slice[p->Q_level] && p->runTime != p->needTime){
            // ����ʱ�����ʱ��Ƭ�����ý��̷ŵ���һ��������β
            p->Q_level++; 
            Q[p->Q_level] = tail_to_tail(Q[p->Q_level], p);
            p->acc_time = 0; // �ۼ�����ʱ������
        }
        // ��ӡ��ǰ���еĽ���
        show_run(p);
        p->runTime = 'W'; // ����״̬,�ȴ���һ������
    }
    // Q[1] Q[2] ��Ϊ�գ�Q[3] �Ƿ��н���
    else if(Q[3] != nullptr){
        // ȡ�����ȼ���ߵĽ���
        PCB* p = Q[3];
        // ���иý���
        p->state = 'R';
        p->runTime++;
        p->zTime++;
        p->acc_time++;
        // ��ӡ��ǰ���еĽ���
        show_run(p);
        p->runTime = 'W'; // ����״̬,�ȴ���һ������
    }
    // Q[1] Q[2] Q[3] ��Ϊ��
    else{
        cout << "---- �����Ѿ�ȫ�����----" << endl;
        exit(0);
    }
}

int main(){


    // ���������
    srand((unsigned)time(NULL));

    cout << "------------------------------------------------------------------------" << endl;
    PCB* readyList = createPCB(10);
    super_sort(readyList);
    show(readyList);
    cout << "------------------------------------------------------------------------" << endl << endl;;
   
    cout << "--- ����ϵͳʵ��1 ---" << endl;
    cout << "1. ������������ȵ����㷨" << endl;
    cout << "2. ʱ��Ƭ��ת�����㷨" << endl;
    cout << "3. �༶�������е����㷨,��ռʽ" << endl;
    cout << "---------------------" << endl;

    cout << "��ѡ������㷨��" << endl;
    int select;
    cin >> select;
    cout << endl;
    
    switch(select){
        case 1:
            // ��ǰ�������г���
            int len;
            len = space(readyList);

            while (len != 0 && readyList != nullptr)
            {
                char ch = getchar();
                HPS(readyList);
                // ����״̬
                readyList->state = 'W';
                // �Ѿ�������Ľ��̳���
                if(readyList->runTime == readyList->needTime){
                    // ��ӡ��ʾ
                    cout << ">>>>>>>> ����" << readyList->name << "�Ѿ�������ϣ����� <<<<<<<<" << endl << endl;
                    readyList = destroy(readyList, readyList);
                }
                if(len == 0 || readyList == nullptr){
                    cout << "---- �����Ѿ�ȫ�����----" << endl;
                    exit(0);
                }
                super_sort(readyList);
                show(readyList);
                len = space(readyList);

                cout << "�����������" << endl;
                ch = getchar();

            }
        case 2:
            // ��תʱ��
            int sum;
            sum = 0;
            // ��ǰ�������г���
            int len2;
            len2 = space(readyList);
            while(len2 != 0 && readyList != nullptr){
                char ch = getchar();
                RR(readyList);
                // ����״̬
                readyList->state = 'W';
                // �Ѿ�������Ľ��̳���
                cout << ">>>>>>>>ƽ����תʱ�䣺" << (float)sum/10 << endl << endl;
                if(readyList->runTime == readyList->needTime){
                    // ��ӡ��ʾ
                    cout << ">>>>>>>> ����" << readyList->name << "�Ѿ�������ϣ����� <<<<<<<<" << endl << endl;
                    sum += readyList->zTime;
                    readyList = destroy(readyList, readyList);

                }
                len2 = space(readyList);
                if(len2 == 0 || readyList == nullptr){
                    cout << "ƽ����תʱ�䣺" << (float)sum/10 << endl;
                    cout << "---- �����Ѿ�ȫ�����----" << endl;
                    exit(0);
                }               
                else{
                    // ���к󣬽��ý��̷ŵ���β
                    readyList = head_to_tail(readyList);
                }
                show(readyList);
                cout << "�����������" << endl;
                ch = getchar();
            }
            break;

        case 3:

            getchar();
            // ����ʱ��
            int time;
            time = 0;

            // 3���������� Q[1] Q[2] Q[3]
            PCB* Q[4];
            Q[1] = createPCB(1);
            Q[2] = createPCB(1);
            Q[3] = createPCB(1);

            // ��ǰ�������г���
            int Q1_len, Q2_len, Q3_len;
            Q1_len = space(Q[1]);
            Q2_len = space(Q[2]);
            Q3_len = space(Q[3]);

            // �����������
            cout << "��������1:" << endl; 
            show(Q[1]);
            cout << "��������2:" << endl;
            show(Q[2]);
            cout << "��������3:" << endl;
            show(Q[3]);
            



            // 3���������ж���Ϊ��ʱ
            while((Q1_len != 0 && Q2_len != 0 && Q3_len != 0 ) || (Q[1] != nullptr && Q[2] != nullptr && Q[3] != nullptr)){
                system("clear");

                // �Ƿ�Ҫ�ֶ���������
                cout << "�Ƿ�Ҫ�����½���(Y/N)? " << endl;
                if(getchar() == 'Y'){
                    PCB* tmp = createPCB();
                    tmp->Q_level = 1;
                    // ����Q[1] ��β
                    Q[1] = tail_to_tail(Q[1], tmp);
                    cout << "����ʱ�䣺" << time << endl;
                    cout << "�Ѿ������������1" << endl << endl;
                    Q1_len = space(Q[1]);
                    show(Q[1]);
                }


                // ���ö༶�������е����㷨
                MFQ(Q);

                // ������µľ�������
                cout << "��������1:" << endl;
                show(Q[1]);
                cout << "��������2:" << endl;
                show(Q[2]);
                cout << "��������3:" << endl;
                show(Q[3]);

                getchar();
                cout << "�����������" << endl;
                time++; // ����ʱ���1
                getchar();


                

            }
    

            break;
        default:
            cout << "�������" << endl;
            break;
    }
    

    return 0;
}