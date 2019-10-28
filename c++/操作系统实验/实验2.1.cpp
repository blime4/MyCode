//สตั้2.1
#include<stdio.h>
#include<unistd.h>
#include<cstdlib>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;
int main()
{
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