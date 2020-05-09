#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>
#include<sys/msg.h>


#define KEY 1234
#define TEXT_SIZE 48

struct msgbuffer {
    long mtype;
    char mtext[TEXT_SIZE];
}msgp;

int main(){
    int msgid;
    msgid = msgget(KEY,IPC_CREAT|0600);
    if(fork()==0){
        msgp.mtype = 1;
        strcpy(msgp.mtext,"Hi! I am child process!\n");
        msgsnd(msgid,&msgp,TEXT_SIZE,0);
        // return;
    }else{
        sleep(3);
        msgrcv(msgid,&msgp,TEXT_SIZE,0,0);
        printf("parent receive mtext: %s.",msgp.mtext);
        msgctl(msgid,IPC_RMID,NULL);
    }
}