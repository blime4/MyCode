#include<iostream>
#include<fstream>

#define process 5   //��������
#define resource 3  //��Դ��

using namespace std;

int Available_xsb[process];
int Max_xsb[process][resource];
int Allocation_xsb[process][resource];
int Need_xsb[process][resource];
int Work_xsb[process][resource];
int WorkAll[process][resource];
int path[process];

void read();
int Banker(int,int[][resource]);
int Safe(int[],int[][resource],int[][resource]);
void print(int);

int main(){
    read();
    int i,N=0;
    int Request_xsb[process][resource];

    while(N!=-1){
        cout<<"\n����������ԴRequest[���̺�i][��Դ����j]:\n";
        cout<<"����i = ";
        cin>>i;
        cout<<"������Դ����(A B C) = ";
        for(int m=0; m<resource;m++){
            cin>>Request_xsb[i][m];
        }
        cout<<endl;
        int result = Banker(i, Request_xsb);
        cout<<"\n��Դ����--\n";
        print(result);
        cout<<"\n����N(��N=-1ʱ�˳�):\n";
        cin>>N;
    }
}

void read(){
    ifstream inFile1("Alldata.txt",ios::in);
    if(!inFile1)
        cerr<<"File open error."<<endl;
    else{
        char c;
        while((c=inFile1.get())!=EOF)
            cout<<c;
        cout<<endl;
        inFile1.close();
    }
    ifstream inFile2("data.txt",ios::in);
    if(!inFile2)
        cerr<<"File open error."<<endl;
    else {
        int data;
        for(int j=0; j<process;j++) {
            for(i=0;i<resource;i++){
                inFile2>>data;
                Max_xsb[j][i]=data;
            }
            for(i=0;i<resource; i++){
                inFile2>>data;
                Allocation_xsb[j][i]=data;
            }
            for(i=0;i<resource; i++){
                inFile2>>data;
                Need_xsb[j][i]=data;
            }
            if(j==0){
                for(i=0;i<resource; i++){
                    inFile2>>data;
                    Available_xsb[i]=data;
                }
            }
        }
        inFile2.close();
    }
}

int Banker(int i,int Request_xsb[][resource]){
    for(int m=0; m<resource; m++){
        if(Request_xsb[i][m]>Need_xsb[i][m]){
            cout<<"������Դ���������ֵ��"<<endl;
            return 0;
        } else if(Request_xsb[i][m]>Available_xsb[i][m]){
            cout<<"���㹻��Դ��p["<<i<<"]��ȴ���"<<endl;
            return 0;
        }
    }
    for (int j = 0; j<resource; j++)
    {
        Available_xsb[j]=Available_xsb[j]-Request_xsb[i][j];
        Allocation_xsb[i][j]=Allocation_xsb[i][j]+Request_xsb[i][j];
        Need_xsb[i][j]=Need_xsb[i][j]-Request_xsb[i][j];
    }

    int n =Safe(Available_xsb,Need_xsb,Allocation_xsb);
    cout<<endl;
    
    if(n==process){
        cout<<"��ȫ״̬�����Խ���Դ�����p["<<i<<"]"<<endl;
    }else{
        cout<<"����ȫ״̬����������Դ��p["<<i<<"]"<<endl;
    }
    return n;
}

int Safe(int Available_xsb[],int Need_xsb[][resource],int Allocation_xsb[][resource]){
    int i=j=m=n=0;
    int Work[resource],Finish_xsb[process]={0,0,0,0,0};
    for(int r=0; r<resource;r++){
        Work[r]=Available_xsb[r];
    }
    while(i<process){
        if(Finish_xsb[i]==0){
            while(j<process&&Need_xsb[i][j]<=Work[j])
                j++;
            if(j==resource){
                for(int k=0;k<resource;k++){
                    Work_xsb[i][k]=Work[k];
                    Work[k]=Work[k]+Allocation_xsb[i][k];
                    WorkAll[i][k]=Work[k];
                }
                Finish_xsb[i]=1;
                path[m]=i;
                i=-1;
                m++;
            }
        }
        j=0;
        i++;
    }
    for(int p=0; p<process;p++) {
        if(Finish_xsb[p]==1) {
            n++;
        }
    }
    return n;
}

void print(int result){
    if(result==process){
        cout<<"����--��Դ"<<"Work_xsb(A B C)"<<"Need_xsb(A B C)"
            <<"Allocation_xsb(A B C)"<<"Work_xsb+Available(A B C)"
            <<"Finish_xsb"<<endl;
        for(int i=0;i<process;i++){
            cout<<"     "<<"p["<<path[i]<<"] \t";
            for(int j=0;j<resource;j++){
                cout<<Work_xsb[path[i]][j]<<" ";
            }
            cout<<'\t\t';
            for(int j=0;j<resource;j++){
                cout<<Need_xsb[path[i]][j]<<" ";
            }
            cout<<'\t\t';
            for(int j=0;j<resource;j++){
                cout<<Allocation_xsb[path[i]][j]<<" ";
            }
            cout<<'\t\t';
            for(int j=0;j<resource;j++){
                cout<<WorkAll[path[i]][j]<<" ";
            }
            cout<<'\t\t';
            cout<<"true\n";
        }
        cout<<"\n�ҵ���ȫ����{p["<<path[0]<<"]";
        for(int m=1;m<process;m++){
            cout<<",p["<<path[m]<<"]";
        }
        cout<<"}\n";
    }else
    {
        cout<<" ����--��Դ"<<"  Allocation_xsb(A B C)"
            <<" Need_xsb(A B C)"<<"Available_xsb(A B C)\n";
        for(int k=0;k<process;k++){
            cout<<"\tp["<<k<<"]\t\t";
            for(int j=0;j<resource;j++){
                cout<<Allocation_xsb[k][j]<<" ";
            }
            cout<<"\t\t";
            if(k==0){
                for(int j=0;j<resource;j++){
                    cout<<Allocation_xsb[j]<<" ";
                }
            }
            cout<<"\n";
        }
    }
    
}