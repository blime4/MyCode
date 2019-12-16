#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int n,Money;
int Max_happy;
int need[100];
int happy[100];

void dfs(int index, int sum_need,int sum_happy){
    if(sum_need>Money){             //当所需要的钱超过能在该城市花销的钱，
        index=n;                    //直接跳出dfs，
        sum_happy=-1;               //变得不再快乐。
    }
    if(index==n){
        if(sum_happy > Max_happy){  //发现了更加快乐的选择
            Max_happy=sum_happy;    //更新最大快乐值
        }
        return ;
    }
    dfs(index+1,sum_need,sum_happy);
    dfs(index+1,sum_need+need[index],sum_happy+happy[index]);
    
}