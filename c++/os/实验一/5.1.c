#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
void waiting(),stop(),alarming();
int wait_mark;
int main(){
    int p1,p2,stdout;
    while((p1=fork())==-1);//�����ӽ���p1
    if(p1>0){
        while((p2=fork())==-1);//�����ӽ���p2
        if(p2>0){
            wait_mark=1;
            signal(SIGINT,stop);//���յ�^C�źţ�תstop
            signal(SIGALRM,alarming);//����SIGALRM
            waiting();
            kill(p1,16); //��p1�����ж��ź�16 
            kill(p2,17);//��P2�����ж��ź�17 
            wait(0);//ͬ��
            wait(0);
            printf("Parent process is killed!\n");
            exit(0);
        }
        else{
            wait_mark=1;
            signal(17,stop);//�ӵ����ж��ź�17��תstop �Զ����ź�
            signal(SIGINT,SIG_IGN);//����^C�ź�
            while(wait_mark!=0);
            lockf(stdout,1,0);
            printf("Child process 2 is killed by parent!\n");
            lockf(stdout,0,0);
            exit(0);
        }
    }
    else{
        wait_mark=1;
        signal(16,stop);
        signal(SIGINT,SIG_IGN);//����^C�ź�
        while(wait_mark!=0){
            lockf(stdout,1,0);
        }
        printf("Child process 1 is killed by parent!\n");
        lockf(stdout,0,0);
        exit(0);
    }
}

void waiting(){
    sleep(5);
    if(wait_mark!=0);
    while(wait_mark!=0);
}

void alarming(){
    wait_mark=0;
}

void stop(){
    wait_mark=0;
}

