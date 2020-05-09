#include<unistd.h>
#include<signal.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int pid1,pid2;
int main(){
    int fd[2];
    char outpipe[100],inpipe[100];
    pipe(fd);
    while((pid1 = fork())==-1);
    if(pid1==0){
        lockf(fd[1],1,0);
        sprintf(outpipe,"child 1 process is sending message!,child 1 process is sending message!");
        write(fd[1],
        outpipe,100);
        // sleep(5);
        lockf(fd[1],0,0);
        exit(0);
    }
    else{
        while((pid2=fork())==-1);
        if(pid2==0){
            lockf(fd[1],1,0);
            sprintf(outpipe,"child 2 process is sending message!,child 2 process is sending message!");
            write(fd[1],outpipe,100);
            // sleep(5);
            lockf(fd[1],0,0);
            exit(0);
        }
        else{
            wait(0);
            read(fd[0],inpipe,100);
            printf("%s\n",inpipe);
            wait(0);
            read(fd[0],inpipe,100);
            printf("%s\n",inpipe);
            exit(0);
        }
    }
}
