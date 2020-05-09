#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<stdio.h>

#define KEY 1234
#define SIZE 1024


int main(){
    int shmid;
    char *shmaddr;
    struct shmid_ds buf;
    shmid = shmget(KEY, SIZE,IPC_CREAT|0600);
    if(fork()==0){
        shmaddr = (char * )shmat(shmid,NULL,0);
        strcpy(shmaddr,"Hi! I am child process!\n");
        shmdt(shmaddr);
        // return;
    }else{
        sleep(3);
        shmctl(shmid,IPC_STAT,&buf);
        printf("shm_segsz = %d bytes\n",buf.shm_segsz);
        printf("shm_cpid = %d bytes\n",buf.shm_cpid);
        printf("shm_lpid = %d bytes\n",buf.shm_lpid);
        shmaddr = (char *)shmat(shmid,NULL,0);
        printf("%s",shmaddr);
        shmdt(shmaddr);
        shmctl(shmid,IPC_RMID,NULL);
    }
}



