#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>
void waiting(),stop(),alarming();
int wait_mark;
int main(){
    int p1,p2,stdout;
    while((p1=fork())==-1);//创建子进程p1
    if(p1>0){
        while((p2=fork())==-1);//创建子进程p2
        if(p2>0){
            wait_mark=1;
            signal(SIGINT,stop);//接收到^C信号，转stop
            signal(SIGALRM,alarming);//闹钟SIGALRM
            waiting();
            kill(p1,16); //向p1发软中断信号16 
            kill(p2,17);//向P2发软中断信号17 
            wait(0);//同步
            wait(0);
            printf("Parent process is killed!\n");
            exit(0);
        }
        else{
            wait_mark=1;
            signal(17,stop);//接到软中断信号17，转stop 自定义信号
            signal(SIGINT,SIG_IGN);//忽略^C信号
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
        signal(SIGINT,SIG_IGN);//忽略^C信号
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

