#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include<signal.h>

void handler(){
    printf("hello\n");
}

main(){
    signal(SIGUSR1,(__sighandler_t)handler);
    raise(SIGUSR1);
}