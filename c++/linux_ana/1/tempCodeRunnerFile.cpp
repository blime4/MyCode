#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    int pid;
    pid = fork();
    if(pid < 0){
        printf("fork failed!\n");
        exit(1);
    }else if(pid==0){
        printf("this is child process!,pid=%d\n", getpid());
        execl("/bin/ps","ps",NULL);
    }else{
        printf("this is parent process!,pid=%d\n", getpid());
        sleep(10);
    }
}