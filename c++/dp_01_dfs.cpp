#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int n,Money;
int Max_happy;
int need[100];
int happy[100];

void dfs(int index, int sum_need,int sum_happy){
    if(sum_need>Money){             //������Ҫ��Ǯ�������ڸó��л�����Ǯ��
        index=n;                    //ֱ������dfs��
        sum_happy=-1;               //��ò��ٿ��֡�
    }
    if(index==n){
        if(sum_happy > Max_happy){  //�����˸��ӿ��ֵ�ѡ��
            Max_happy=sum_happy;    //����������ֵ
        }
        return ;
    }
    dfs(index+1,sum_need,sum_happy);
    dfs(index+1,sum_need+need[index],sum_happy+happy[index]);
    
}