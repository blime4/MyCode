#include<stdio.h>
#include<algorithm>
#include<fstream>
#include<vector>
#include<iostream>

using namespace std;

int init_pos;
int len;
int count_xsb;
int *data;
vector<int>move_xsb;

void read_xsb();
void FCFS_xsb();
void SSTF_xsb();
void SCAN_xsb();
void path_xsb();

int main(){
    read_xsb();
}

void read_xsb(){
    fstream input("all_data.txt",ios::in);
    if(!input){
        cerr << "File open error!\n";
    }else{
        int n;
        input >> n;
        while(n--){
            input >> init_pos;
            input >> len;
            data = new int[len];
            for(int i = 0; i < len; i++){
                input>>data[i];
            }
            FCFS_xsb();
            SSTF_xsb();
            SCAN_xsb();
        }        
    }
}

void FCFS_xsb(){
    puts("------FCFS------\n\n");
    count_xsb=0;
    move_xsb.clear();
    int step=init_pos;
    for(int i = 0; i < len; i++){
        move_xsb.push_back(data[i]);
        count_xsb += abs(step-data[i]);
        step = data[i];
    }
    path_xsb();
}

void SSTF_xsb(){
    puts("------SSTF------\n\n");
    count_xsb = 0;
    move_xsb.clear();
    int step=init_pos;
    sort(data,data+len);
    int pos=init_pos;
    int left;
    int right;
    for(int i = 0; i < len; i++){
        if(init_pos>=data[i]){
            left=i-1;
            right=i;
            break;
        }
    }
    int flag=0;
    while(flag<len){
        if(right>=len||left>=0&&abs(data[right]-pos)>abs(data[left]-pos)){   //右边大于左边，加左0
            count_xsb += abs(data[left]-pos);
            move_xsb.push_back(data[left]);
            pos = data[left];
            left--;
        }else{
            count_xsb += abs(data[left]-pos);
            move_xsb.push_back(data[right]);
            pos = data[right];
            right++;
        }
        flag++;
    }
    path_xsb();
}
void SCAN_xsb(){
    puts("------SCAN------\n\n");
    count_xsb = 0;
    move_xsb.clear();
    int step=init_pos;
    sort(data,data+len);
    int pos=init_pos;
    int left;
    int right;
    for(int i = 0; i < len; i++){
        if(init_pos>=data[i]){
            left=i-1;
            right=i;
            break;
        }
    }
    while(right<len){
        count_xsb += abs(data[right]-pos);
        move_xsb.push_back(data[right]);
        pos = right;
        right++;
    }
    while(left>=0){
        count_xsb += abs(data[left]-pos);
        move_xsb.push_back(data[left]);
        pos = left;
        left--;
    }
    path_xsb();
}

void path_xsb(){
    for(auto val:move_xsb){
        cout << val << "-->";
    }
    cout<<endl;
    cout<<"The total distance the head moves:  "<<count_xsb<<endl;
    cout<<"The average distance the head moves:"<<count_xsb/len<<endl;
}