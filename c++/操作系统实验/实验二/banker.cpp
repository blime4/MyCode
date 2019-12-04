#include <iostream>
#include <fstream>

#define PROGRESS 5
#define RESOURCE  3   

using namespace std;

int Available_xsb[RESOURCE];
int sign[PROGRESS];
int work[PROGRESS][RESOURCE];
int work_Allocation_xsb[PROGRESS][RESOURCE];
int Max_xsb[PROGRESS][RESOURCE];
int Allocation_xsb[PROGRESS][RESOURCE];
int Need_xsb[PROGRESS][RESOURCE];

void init(){
        ifstream inFile1("output.txt",ios::in);
        if(!inFile1)
              cerr<<"File open error."<<endl;
        else {
                char c;
                while((c=inFile1.get())!=EOF)
                        cout<<c;
                cout<<endl;
                inFile1.close();
        }
        ifstream inFile2("blime.txt",ios::in);
        if(!inFile2)
              cerr<<"File open error."<<endl;
        else{
                int data;
                for(int j = 0;j < PROGRESS;j++) {
                for(int i = 0;i < RESOURCE;i++) {
                    inFile2>>data;
                    Max_xsb[j][i]=data;
                }
                for(int i = 0;i < RESOURCE;i++) {
                    inFile2>>data;
                    Allocation_xsb[j][i]=data;
                }
                for(int i = 0;i < RESOURCE;i++) {
                    inFile2>>data;
                    Need_xsb[j][i]=data;
                }
                if(j==0) {
                    for(int i = 0;i < RESOURCE;i++) {
                        inFile2>>data;
                        Available_xsb[i]=data;
                    }
                }
               }
                inFile2.close();
        }

}
int Safe_inspection(int Available_xsb[],int Need_xsb[][RESOURCE],int Allocation_xsb[][RESOURCE]) {
        int i=0,j=0,m=0,n=0;
        int Work[RESOURCE],Finish[PROGRESS] = {0,0,0,0,0};
        for(int r = 0;r < RESOURCE;r++) 
                Work[r] = Available_xsb[r];
        while(i < PROGRESS) {
                if(Finish[i] == 0){
                        while(j < RESOURCE && Need_xsb[i][j] <= Work[j] )
                                j++;
                        if(j == RESOURCE) {
                                for(int k = 0;k < RESOURCE;k++){
                                        work[i][k] = Work[k];
                                        Work[k] = Work[k]+Allocation_xsb[i][k];
                                        work_Allocation_xsb[i][k] = Work[k];
                                }
                                Finish[i]=1;
                                sign[m]=i;  
                                i=-1;m++;
                        }
                }
                j=0;i++;
        }
        for(int p = 0;p < PROGRESS;p++){
               if(Finish[p] == 1)
                        n++;   
        }
        return n;     
}
int bank_xsb (int i,int Request[][RESOURCE]){
        for(int m = 0;m < RESOURCE;m++) {
                if(Request[i][m] > Need_xsb[i][m]){
                        cout<<"request resource over Max!"<<endl;
                        return 0;
                } else if(Request[i][m] > Available_xsb[m]) {
                        cout<<"resource insufficient，p["<<i<<"] need wait!"<<endl;
                        return 0;
                }
        }
        for(int j = 0;j < RESOURCE;j++) {
                Available_xsb[j] = Available_xsb[j] - Request[i][j];
                Allocation_xsb[i][j] = Allocation_xsb[i][j] + Request[i][j];
                Need_xsb[i][j] = Need_xsb[i][j] - Request[i][j];
        }
        int n = Safe_inspection(Available_xsb,Need_xsb,Allocation_xsb);
        cout<<endl;

        if(n == PROGRESS) {
                cout<<"safe state，allocate resource to "<<"P["<<i<<"]!"<<endl;
        }else {
                cout<<"unsafe state，cannot allocate resource to "<<"P["<<i<<"]!"<<endl;
        }
        return n;
}


void Print(int result) {
        if(result == PROGRESS) {
                cout<<" progress\\Resources"<<" Work(A B C)"<<" Need_xsb(A B C)"
                    <<" Allocation_xsb(A B C)"<<" Work+Available_xsb(A B C)"<<" Finish";
                cout<<endl;
                for(int i = 0;i < PROGRESS;i++) {
                        cout<<"    "<<"P["<<sign[i]<<"]  "<<'\t';
                        for(int j = 0;j < RESOURCE;j++)
                               cout<<work[sign[i]][j]<<" ";
                        cout<<'\t'<<'\t';
                        for(int j = 0;j < RESOURCE;j++)
                               cout<<Need_xsb[sign[i]][j]<<" ";
                        cout<<'\t'<<'\t';
                        for(int j = 0;j < RESOURCE;j++)
                               cout<<Allocation_xsb[sign[i]][j]<<" ";
                        cout<<'\t'<<'\t';
                        for(int j = 0;j < RESOURCE;j++)
                               cout<<work_Allocation_xsb[sign[i]][j]<<" ";
                        cout<<'\t'<<'\t';
                        cout<<"true"<<endl;
                }
                cout<<endl<<"Find safe sequence｛P["<<sign[0]<<"]";
                for(int m = 1;m < PROGRESS;m++){
                        cout<<", P["<<sign[m]<<"]";
                }
                cout<<"}"<<endl;

        } else {
                cout<<"   progress\\Resources "<<"  Allocation_xsb(A B C)"<<"   Need_xsb(A B C)"<<"   Available_xsb(A B C)";
                cout<<endl;
                for(int k = 0;k < 5;k++){
                        cout<<'\t'<<"P["<<k<<"]"<<'\t'<<'\t';
                        for(int j = 0;j < 3;j++)
                                cout<<Allocation_xsb[k][j]<<" ";
                        cout<<'\t'<<'\t';
                        for(int j = 0;j < 3;j++)
                                cout<<Need_xsb[k][j]<<" ";
                        cout<<'\t'<<'\t';
                        if(k == 0) {
                                for(int j = 0;j < 3;j++)
                                cout<<Available_xsb[j]<<" ";
                        }
                        cout<<endl;
                }
        }
}
      

int main()
{
        puts("计科173谢绍波");
        init();
        int i,N=0;
        int Request[PROGRESS][RESOURCE];

        while(N!=-1) {
                cout<<endl<<"Please input request resource Request[PROGRESS i][resource j]:"<<endl;
                cout<<"PROGRESS i = ";
                cin>>i;
                cout<<"Resource (A B C) =  ";
                for(int m = 0;m < RESOURCE;m++)
                        cin>>Request[i][m];
                cout<<endl;
                int result = bank_xsb(i,Request);
                cout<<endl<<"resource allocation table ："<<endl;
                Print(result);
                cout<<endl<<"Please input N(quit when N=-1)："<<endl;
                cin>>N;
        }
}
