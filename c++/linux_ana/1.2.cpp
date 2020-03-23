#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h> 

void *thread(void*){
    int i;
    for(i = 0;i<3;i++){
        printf("This is a pthread\n");
        sleep(1);
    }
}
void *thread2(void*){
    int i;
    for(i = 0;i<3;i++){
        printf("This is a 2\n");
        sleep(2);
    }
}

int main(){
    pthread_t id,id2;
    int i,ret,ret2;
    ret = pthread_create(&id,NULL,thread,NULL);
    ret2 = pthread_create(&id2,NULL,thread2,NULL);
    if(ret!=0){
        printf("Create pthread error\n");
        exit(1);
    }
    for(i=0;i<3;i++){
        printf("This is the main process\n");
        sleep(3);
    }
    pthread_join(id,NULL);
    return 0;
}