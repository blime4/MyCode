#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdlib>
#include<signal.h>
#include<sys/ipc.h>
#include<sys/msg.h>
//client.cpp

#define MSGKEY 75
struct magform{
    long mtype;
    char mtext[1000];
}msg;
int msgqid;
void client(){
    int i;
    msgqid=msgget(MSGKEY,0777);
    for(int i=10;i>=1;i--){
        msg.mtype=i;
        printf("(client)sent 1706100109谢绍波\n");
        msgsnd(msgqid,&msg,1024,0);
    }
    exit(0);
}
int main(){
    client();
}