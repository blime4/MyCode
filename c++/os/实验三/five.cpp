#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<malloc.h>
#include<iostream>
//int date[1000];


struct Date{
    int date;
    bool flag;//访问标志
}date[1000];

int move[1000];//磁头移动轨迹
int moveNum;//移动的总磁道数
int N;//磁道总数

void init(){
    srand((unsigned)time(NULL));
    //N =rand()%1001;
    N=10;
    for(int i=0; i<N; i++){
        date[i].date=rand()%1001;
        date[i].flag=false;
        move[i]=0;
    }
    //move[1000]={0};
    printf("随机序列");
    for (int i=0;i<N; i++){
        printf("%d ",date[i].date);
    }
}



void FCFS(){
    for(int i=0; i<N;i++){
        move[i]=date[i].date;//磁头移动轨迹
    }
    //moveNum=abs(move[0]-initPos);
    for(int i=1; i<N; i++){
        moveNum = moveNum+ abs(move[i]-move[i-1]);
    }
}

void SSTF(){
    int arr[1000];
    int temp;
    for(int i=0; i<N; i++){
        arr[i] = date[i].date;
    }
    //冒泡排序
    for(int i=0; i<N; i++){
        for(int j=i;j<N;j++){
            if(arr[i]>arr[j])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    printf("冒泡排序：");
    for (int i = 0; i<N; i++){
        printf("%d ",arr[i]);
    }

    int a=0;
    while(date[0].date!=arr[a]){
        a++;
    }//a找到磁头初始位置
    int left =a-1;
    int right=a+1;
    move[0]=arr[a];//move[]移动顺序数组 。 arr[]是冒泡排序之后的数组
    //移动顺序
    for(int i=0;i<N-1; i++){
        //左边距离小于右边距离。左边的数放进move[i+1]
        if(right>=N||move[i]-arr[left] <= arr[right]-move[i]){
            if(left>=0){
                
                move[i+1]=arr[left];
                // printf("%d ",move[i+1]);
                left--;
                continue;
            }
        }
        //左边距离大于右边距离.右边的数放进move[i+1]
        if(left<0||move[i]-arr[left] > arr[right]-move[i]){
            if(right<=N){
                move[i+1]=arr[right];
                // printf("%d ",move[i+1]);
                right++;
                continue;
            }
        }
    }
    printf("移动顺序：");
    for(int i = 0; i<N; i++){
        printf("%d ",move[i]);
    }


}

// void SSTF(){
//     move[0]=date[0].date;
//     int instance,min;//距离
//     int len = N;
//     Bubble(date);

//     min=abs(date[1].date-date[0].date);
    
//     int m;
//     for(int i=1; i<N; i++){
//         for(int n=1; n<N; n++){
//             //if(date[i].flag==false){
//             if(date[n].flag==false){//未访问的磁道
//                 instance=abs(date[n].date-move[n-1]);//计算磁头距离            
//                 //寻找最短磁头距离
//                 if(instance<min){
//                     min=instance;

//                 }
//             }    
//             move[i]=date[n].date;
//             date[n].flag=true;
                
            
//         }
//     }
// }

//磁头移动轨迹,移动的总磁道数
void output(){
    printf("磁道总数：%d \n",N);
    // for(int i=0; i<N; i++){
    //     printf("%d ",date[i]);
    // }
    printf("磁头移动轨迹：");
    for(int i=0; i<N-1; i++){
        printf("%d->",move[i]);
    }
    printf("%d",move[N-1]);
    printf("\n移动的总磁道数:%d",moveNum);
}


int main(){
    init();
    // printf("FCFS:\n");
    // FCFS();
    SSTF();
    output();
}