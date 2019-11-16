
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
    printf("计科173谢绍波1706100109\n");
    pid_t pid;
    pid =fork();
    switch (pid){
        case -1:
            printf("fork failed!\n");
            exit(1);
        case 0:
            execl("/bin/ls","ls","-l","-color",NULL);
            printf("exec failed!\n");
            exit(1);
        default:
            wait(NULL);
            printf("ls completed!\n");
            exit(0);
    }
}