#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdlib>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/msg.h>
//server.cpp

#define MSGKEY 75
struct msgform{
    long mtype;
    char mtext[1000];
}msg;
int msgqid;
void server(){
    msgqid=msgget(MSGKEY,0777|IPC_CREAT);
    do{
        msgrcv(msgqid,&msg,1030,0,0);
        printf("(server)received 1706100109谢绍波\n");
    }while(msg.mtype!=1);
    msgctl(msgqid,IPC_RMID,0);
    exit(0);
}
int main(){
    server();
}