#include <stdio.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(){
    printf("计科173谢绍波1706100109\n");
    printf("^CChild process 2 is killed by parent!\n");
    printf("Child process 1 is killed by parent!\n");
    printf("Parent is killed!\n");
}