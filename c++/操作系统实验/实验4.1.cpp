//สตั้4.1

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdlib>

int main(){
    time_t t;
    FILE *fp =fopen("/var/log/Mydaemon.log","a");
    setlinebuf(fp);
    pid_t pid = fork();
    if(pid>0){
        printf("Daemon on duty\n");
        exit(0);
    }
}