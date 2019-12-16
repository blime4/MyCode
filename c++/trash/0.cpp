#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int dp[20][20],x[20]; ///定义为全局变量
void traceback(int n,int c,int w[])
{
    for(int i=n;i>1;i--)
    {
        if(dp[i][c]==dp[i-1][c]) ///表示第 i 个和 第 i-1 个所能挑到的最大值相等
            x[i]=0; ///表示此处 i 物品没有被挑选到
        else{
            x[i]=1; ///表示此处 i 物品被挑选到
            c-=w[i]; /// 需减去当前的重量w[i]
        }
    }
    x[1]=(dp[1][c]>0)?1:0; ///上面循环中没有判断1，只要>0就可以证明拿了
}
int main()
{
    int v[]={4,8,15,1,6,3}; ///为便于读者阅读，初始化
    int w[]={5,3,2,10,4,8};
    int n=6,c=20;
 
    memset(dp,0,sizeof(dp)); ///小提醒：只能赋0，或-1
    for(int i=1;i<=n;i++)  ///从第1个到第i个物品中挑选出总重量不超过j的物品时总价值的最大值
    {
        for(int j=1;j<=c;j++)
        {
            if(j>=w[i])
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i]);
            else
                dp[i][j]=dp[i-1][j]; ///表示跟前i-1个一样
        }
    }
    for(int i=1;i<=n;i++){  ///输出每种情况
        for(int j=1;j<=c;j++)
        printf("%d ",dp[i][j]);
        putchar('\n');
    }
    printf("总价值%d\n",dp[n][c]); ///总价值
    traceback(n,c,w);  ///我们可以找出到底是挑了哪几个物品
    for(int i=1;i<=n;i++){
        if(x[i]) printf("%d ",i);
    }
    putchar('\n');
    return 0;
}
 