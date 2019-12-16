#include<iostream>
#include<string>
using namespace std;

string tobin(int weishu,string ans,int i){
    int i_t = i;
    int a[i]={0};
    int j=0;
    while(i){
        a[j]=i%2;
        i/=2;
        j++;
    }
    for(int i = i_t-1; i>=0; i--){
        string tmp = to_string(a[i]);
        ans += tmp;
    }
    return ans;
}
string PCM(int n){
    string ans;

    if(n>=0){  //µ±0È¡1
        ans='1';
        int i= 10;
        while(n-(1<<i)<0){i--;}
        if(i>=0&&i<16) i=0; 
        else i-=3;
        ans=tobin(3,ans,i);
        
    }else{
        ans='0';
    }
    return ans;
}

int main(){
    int n;
    cin>>n;
    string ans=PCM(n);
    cout<<ans<<endl;

}