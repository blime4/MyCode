

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main(){
    printf("计科173谢绍波1706100109\n");
    time_t t;                   
    FILE *fp;               //????
    fp=fopen("./Mydaemon.log","a");//????
    setlinebuf(fp); //?????
    pid_t pid;                //???
    pid=fork();
    if(pid>0){
        printf("Daemon on duty!\n");
        exit(0);
    }
    else if(pid<0){
        printf("Can't fork!\n");
        exit(-1);
    }
    while(1){
        if(fp>=0){
        sleep(60);             //???????????????
        printf("Daemon on duty!\n");
        t=time(0);
        fprintf(fp,"The current time is %s\n",asctime(localtime(&t)));
        }
    }
    fclose(fp);//????
}
