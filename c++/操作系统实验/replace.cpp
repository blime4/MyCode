#include<iostream>
#include<fstream>
#include<vector>
#include <algorithm>
using namespace std;

vector<int> kuaishu;  //内存块数
vector<int> yehaoshu; //页号数
vector<int> yehao;  //请求页号

void read();
void OPT();
void FIFO();
void LRU();
void LFU();


int main(){
    read();
    for_each(kuaishu.begin(), kuaishu.end(),[](int i){cout << i <<" ";});
    cout<<endl;
    for_each(yehaoshu.begin(), yehaoshu.end(),[](int i){cout << i <<" ";});
    cout<<endl;
    for_each(yehao.begin(), yehao.end(),[](int i){
        if (i != -1) cout << i <<" ";
        else cout << endl;
        });
}
void read(){
    fstream input("data.txt",ios::in);
    if(!input){
        cerr << "File open error!\n";
    }else{
        int number;
        int n,m,data;
        input>>number;
        while (number--){
            input>>n;
            kuaishu.push_back(n);
            input>>m;
            yehaoshu.push_back(m);
            while(m--){
                input >> data;
                yehao.push_back(data);      //插入页号
            }
            yehao.push_back(-1);
        }
        input.close();
    }
}

void OPT(){
    /*
    思路：
    if 空槽：
        填入
    */
}