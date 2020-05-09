// #include<stdio.h>
// #include<unistd.h>
// #include<stdlib.h>
// #include<sys/wait.h>

// int main(){
//     int pid;
//     pid = fork();
//     if(pid < 0){
//         printf("fork failed!\n");
//         exit(1);
//     }else if(pid==0){
//         printf("this is child process!,pid=%d\n", getpid());
//         sleep(10);
//     }else{
//         printf("this is parent process!,pid=%d\n", getpid());
//         sleep(10);
//     }
// }



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


// #include<stdio.h>
// #include<stdlib.h>
// #include<pthread.h>
// #include <unistd.h> 

// void *thread_A(void*){
//     for(int i = 0; i <5;i++)
//         printf("AAA %d\n",i);
// }

// void *thread_B(void*){
//     for(int i = 0; i <5;i++)
//         printf("BBB %d\n",i);
// }

// int main(){
//     pthread_t id1,id2;
//     int ret1,ret2;
//     ret1 = pthread_create(&id1, NULL, thread_A, NULL);
//     ret2 = pthread_create(&id2, NULL, thread_B, NULL);
//     pthread_join(id1,NULL);
// }


// #include<stdio.h>
// #include<stdlib.h>
// #include<pthread.h>
// #include <unistd.h> 
// #include <semaphore.h>

// sem_t empty;
// sem_t coca;
// sem_t pepsi;
// pthread_mutex_t work_mutex; 

// void *get_coca(void*){
//     while(1){
//         sem_wait(&empty);
//         pthread_mutex_lock(&work_mutex);
//         printf("进货  一车  可口可乐\n");
//         sem_post(&coca);
//         pthread_mutex_unlock(&work_mutex);
//         sleep(1);
//     }
// }

// void *get_pepsi(void*){
//     while(1){
//         sem_wait(&empty);
//         pthread_mutex_lock(&work_mutex);
//         printf("进货  一车  百事可乐\n");
//         sem_post(&pepsi);
//         pthread_mutex_unlock(&work_mutex);
//         sleep(1);
//     }
// }

// void *sell_coca(void*){
//     while(1){
//         sem_wait(&coca);
//         pthread_mutex_lock(&work_mutex);
//         printf("卖出  一车  可口可乐\n");
//         sem_post(&empty);
//         pthread_mutex_unlock(&work_mutex);
//         sleep(2);
//     }
// }

// void *sell_pepsi(void*){
//     while(1){
//         sem_wait(&pepsi);
//         pthread_mutex_lock(&work_mutex);
//         printf("卖出  一车  百事可乐\n");
//         sem_post(&empty);
//         pthread_mutex_unlock(&work_mutex);
//         sleep(2);
//     }
// }

// int main (){
//     pthread_t t1,t2,t3,t4;

//     sem_init(&empty,0,4);
//     sem_init(&coca,0,0);
//     sem_init(&pepsi,0,0);
//     pthread_mutex_init(&work_mutex,NULL);

//     pthread_create(&t1,NULL,get_coca,NULL);
//     pthread_create(&t2,NULL,get_pepsi,NULL);
//     pthread_create(&t3,NULL,sell_coca,NULL);
//     pthread_create(&t4,NULL,sell_pepsi,NULL);

//     sleep(100000);
// }