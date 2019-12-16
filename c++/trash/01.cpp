#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1100;
int v[MAXN], w[MAXN], N, V, dp[MAXN][MAXN];

int dfs(int step, int cap){
    if(step == 1){
        if(cap >= v[step]) return dp[step][cap] = w[step];
        else return dp[step][cap] = 0;
    }
    if(dp[step][cap]) return dp[step][cap];

    if(cap >= v[step]) return dp[step][cap] = max((dfs(step-1, cap - v[step]) + w[step]), dfs(step-1, cap));
    else return dp[step][cap] = dfs(step-1, cap);
}

int main(){
    cin>>N>>V;
    for(int i=1; i<=N; ++i) cin>>v[i]>>w[i];
    cout<<dfs(N, V)<<endl; 
}