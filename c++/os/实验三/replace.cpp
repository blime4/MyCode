#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include <algorithm>
using namespace std;


void read_xsb();
void OPT_xsb();
void FIFO_xsb();
void LRU_xsb();
void LFU_xsb();

int kuaishu;        //内存块数
int len;            //数据长度
int *data;          //数据

int main(){
    puts("计科173谢绍波1706100109");
    read_xsb();
}
void read_xsb(){
    fstream input("data.txt",ios::in);
    if(!input){
        cerr << "File open error!\n";
    }else{
        int n;
        input >> n;
        while(n--){
            input >> kuaishu;
            input >> len;
            data = new int[len];
            for(int i = 0; i < len; i++){
                input>>data[i];
            }
            for(int i = 0; i < len; i++){
                cout << data[i]<<" ";
            }
            cout << endl;
            OPT_xsb();
            FIFO_xsb();
            LRU_xsb();
            LFU_xsb();
        }
    }
    input.close();
}

void OPT_xsb(){
    /*
    思路：
    if 页框内是否有：
        不变
    elif 空槽：
        填入页框，缺页加一
    else：
        依次查看后面数字，与页框内相同的数在后多少位
        if 找不到:
            直接替换
        elif 大于max:
            max更新
        置换max
        缺页加一
    */
   vector<int>memory;
   int count = 0; //缺页数
   for(int i=0;i<len;i++){
       int item = data[i];
       auto it = find(memory.begin(),memory.end(),item);
       if(it!=memory.end()){    //内存中已经存在
          //什么都不变 
       }else if(memory.size()<kuaishu){
           memory.push_back(item);
        //    count++;
       }else{
           count++;
           int max=i;
           int change_num=0;
           bool found=false;
           for(int j = 0;j<memory.size();j++){
               for(int k =i+1;k<len;k++){
                   if(memory[j]==data[k]){
                       found=true;
                       if(k>max){max=k;change_num=j;}
                       break;
                   }
               }
               if(!found){
                       change_num=j;
                       j=memory.size();
                   }
               found=false;
           }
           memory[change_num]=item;
       }
    //    for(auto val:memory){
    //        cout<<val<<" ";
    //    }
    //    cout<<endl;
   }
   cout<<"\nOPT 缺页数:"<<count<<"\t访问命中率:"<<float(1-float(count)/float(len))<<endl;
}

void FIFO_xsb(){
    /*
    思路：
    if 页框内是否有：
        不变
    // elif 空槽：                          //我们留意到，队列的弹出和添加和缺页数有关，即存在
    //     填入页框，缺页加一                //这次队列要替换的就是，第 缺页数%物理块号 个
    //     把填入页框号放入队列中            //所以不需要用到队列，只需要缺页数就行了。
    // else：
    //     弹出队列头
    //     填入队列头对应的页框号中。
    elif 空槽：
        填入页框，缺页加一
    else:
        缺页+1
        替换缺页数%物理块号
    */
   vector<int>memory;
   int count = 0; //缺页数
    for(int i=0;i<len;i++){
        int item = data[i];
        auto it = find(memory.begin(),memory.end(),item);
        if(it!=memory.end()){    //内存中已经存在
            //什么都不变 
        }else if(memory.size()<kuaishu){
            memory.push_back(item);
            count++;
        }else{
            count++;
            memory[count%kuaishu]=item;
        }
        for(auto val:memory){
           cout<<val<<" ";
        }
        cout<<endl;
    }
    cout<<"FIFO_xsb 缺页数:"<<count-kuaishu<<"\t访问命中率:"<<float(1-float(count-kuaishu)/float(len))<<endl;
}

void LRU_xsb(){
    /*
    思路:
    LRU就是向前版OPT
    */
   vector<int>memory;
   int count = 0; //缺页数
   for(int i=0;i<len;i++){
       int item = data[i];
       auto it = find(memory.begin(),memory.end(),item);
       if(it!=memory.end()){    //内存中已经存在
          //什么都不变 
       }else if(memory.size()<kuaishu){
           memory.push_back(item);
       }else{
           count++;
           int min;
           int change_num=0;
           set<int>temp;
           for(int j=i-1;j>=0;j--){
               temp.insert(data[j]);
               if(temp.size()==kuaishu){
                   min=data[j];
               }
           }
           for(int j=0;j<memory.size();j++){
               if(memory[j]==min){
                   memory[j]=item;
                   break;
               }
           }
       }
    }
    cout<<"LRU_xsb 缺页数:"<<count<<"\t访问命中率:"<<float(1-float(count)/float(len))<<endl;  

}

void LFU_xsb(){
    vector<int>memory;
    int count = 0; //缺页数
    map<int,int>frequency;
    for(int i=0;i<len;i++){
        int item = data[i];
        auto it = find(memory.begin(),memory.end(),item);
        if(it!=memory.end()){   //内存中已经存在
            frequency[item]++;
        }else if(memory.size()<kuaishu){
            memory.push_back(item);
            frequency[item]++;
        }else{
            count++;
            int min=999999;
            int change=0;
            int change_num=0;
            for(auto it=frequency.begin();it!=frequency.end();it++){
                if(it->second<min){
                    min=it->second;
                    change=it->first;
                }
            }
            for(int j=0;j<memory.size();j++){
                if(memory[j]==change){
                    memory[j]=item;
                    break;
                }
            }
            frequency[item]++;
        }
    }
    // for(auto it=frequency.begin();it!=frequency.end();it++){
    //     cout<<it->first<<" "<<it->second<<endl;
    // }
    cout<<"LFU_xsb 缺页数:"<<count<<"\t访问命中率:"<<float(1-float(count)/float(len))<<"\n\n";  

}