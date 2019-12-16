#include<fstream>
#include<iostream>
using namespace std;

#define INTER_COUNT 2           //接口数量
#define TABLE_MAX_CUONT 255     //转发表最大数量

int tablecount = 0;             //转发表数量

struct trantable{               //转发表结构体
    char inter;                 //接口
    char dest;                  
}table[TABLE_MAX_CUONT] = {0,0,0,0};

struct dataframe{               //数据帧结构体
    char source;
    char dest;
};

void update_table(struct dataframe data,int inter){
    //更新转发表
    table[tablecount].dest = data.source;
    table[tablecount].inter = inter;
    tablecount++;       //转发表数量++
}

int search_table(struct dataframe data){
    //查找转发表
    int temp1 = 0,temp2 = 0;
    for(int i = 0; i<tablecount; i++){
        if(table[i].dest == data.dest){
            temp1 = table[i].inter;
        }
        if(table[i].dest == data.source){
            temp2 = table[i].inter;
        }
    }
    if(temp1 == temp2 && temp1 && temp2){
        return 3;
    }
    else if(temp1){
        return temp1;
    }else{
        return 0;
    }
}

int main(){
    int flag;
    struct dataframe data;
    fstream file1("file1.txt"),file2("file2.txt");

    while(!file1.eof()&&!file2.eof()){
        file1>>data.source>>data.dest;
        flag = search_table(data);
        cout<<"数据帧（Source： "<<data.source<<",Destination： "<<data.dest<<") ";
        switch(flag){
            case 0:{
                puts("无法转发");
                update_table(data,1);
                break;
            }
            case 3:{
                puts("在同一接口，不转发");
                break;
            }
            default:{
                cout<<"转发至接口： "<<flag<<endl;
                break;
            }
        }
        file2>>data.source>>data.dest;
        flag = search_table(data);
        cout<<"数据帧（Source： "<<data.source<<",Destination： "<<data.dest<<") ";
        switch(flag){
            case 0:{
                puts("无法转发");
                update_table(data,2);
                break;
            }
            case 3:{
                puts("在同一接口，不转发");
                break;
            }
            default:{
                cout<<"转发至接口： "<<flag<<endl;
                break;
            }
        }
    }
    file1.close();
    file2.close();
}