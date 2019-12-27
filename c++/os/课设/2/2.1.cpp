#include<bits/stdc++.h>

using namespace std;
struct PCB{             //进程控制块PCB
    int pid;            //进程名
    int arr_time;       //到达时间
    int run_time;       //运行时间
    int priority;       //优先级
    char status='n';    //进程状态   n:新建进程  R：运行状态  r:就绪状态 
    friend bool operator < (const PCB& a, const PCB& b){
        if(a.arr_time==b.arr_time){
            return a.priority>b.priority;
        }
        return a.arr_time>b.arr_time;
    }
};
bool cmp(const PCB &a, const PCB &b){return a.priority>b.priority;}
bool comp(const PCB & a, const PCB & b){if(a.arr_time==b.arr_time){return a.priority>b.priority;} return a.arr_time<b.arr_time;}
void create(vector<PCB> &L,int n){
    srand((unsigned int)time(0));
    for(int i = 0; i < n; i++){
        PCB p;
        p.pid = i+1;
        p.arr_time = rand()%15;
        p.run_time = rand()%10+1;
        p.priority = rand()%5;
        L.push_back(p);
    }
    sort(L.begin(), L.end(),comp);
    puts("-----------------初始化进程-----------------");
    puts("进程号--到达时间--运行时间--优先级--进程状态");
    for(auto val : L) { cout<<val.pid<<"\t"<<val.arr_time<<"\t\t"<<val.run_time<<"\t"<<val.priority<<"\t"<<val.status<<endl;}
    puts("-------------------------------------------");
    cout<<endl;
}

void arrival(vector<PCB> &L,vector<PCB> &Q,int &t) {
    bool flag=false;
    while(1){
        if(L.front().arr_time==t){
            L.front().status='r';
            Q.push_back(L.front());
            sort(Q.begin(),Q.end(),cmp);       //seize//灵魂
            L.erase(L.begin());
            flag=true;
        }
        if(L.front().arr_time!=t){
            break;
        }
        if(L.empty()){
            break;
        }
    }
    if(flag){
        cout<<"---当前时间---"<<t<<endl;
        cout<<Q.front().pid<<"进程开始运行\n";
        puts("-----------------初始化队列-----------------");
        puts("进程号--到达时间--运行时间--优先级--进程状态");
        for(auto val : L) { cout<<val.pid<<"\t"<<val.arr_time<<"\t\t"<<val.run_time<<"\t"<<val.priority<<"\t"<<val.status<<endl;}
        puts("-------------------------------------------");
        cout<<endl;
    }
}
void run(vector<PCB> &L,vector<PCB> &Q,int &t){
    //运行队列
    int pi=-1;
    while(1){
        arrival(L,Q,t);
        if(Q.empty()){
            t++;
        }else{
            if(pi!=Q.front().pid){  //灵魂2
                cout<<"当前运行的进程是： "<<Q.front().pid<<endl;
                puts("就绪队列：");
                puts("进程号--到达时间--运行时间--优先级--进程状态");
                Q.front().status='R';
                for(auto val : Q){ cout<<val.pid<<"\t"<<val.arr_time<<"\t\t"<<val.run_time<<"\t"<<val.priority<<"\t"<<val.status<<endl;}
                Q.front().status='r';
                cout<<endl;
                pi=Q.front().pid;
            }
            Q.front().run_time--;
            if(Q.front().run_time==0){
                cout<<Q.front().pid<<"进程运行完成\n";
                cout << "---当前时间---"<<t<<endl;
                Q.erase(Q.begin());
            }else{
                if(Q.front().priority!=0){
                    Q.front().priority--;
                }else Q.front().priority=0;
            }
            t++;
        }
        if(L.empty()&&Q.empty()) break;
    }
}
int main(){
    vector<PCB> L;
    vector<PCB> Q;
    puts("请输入本次进程数n:");
    int n;cin>>n;
    int t = 0;
    create(L, n);
    run(L, Q,t);
}
