#include <bits/stdc++.h>

using namespace std;

//主文件目录和用户文件目录（MFD、UFD），打开文件目录（AFD）


typedef struct UFD{
    string File_name;
    int Start;
    int Protect;
    int File_length;
    int Max_File_length;
    struct UFD *next;
}UFD,*UFD_ptr;

typedef struct MFD
{
	string User_name;
	string User_passwd;
	UFD *Ufd_next;
	int End;
	struct MFD *next;
}MFD,*MFD_ptr;

typedef struct AFD
{
	string File_name;
	int File_length;
	int Start;
	int Protect;
	int Pointer;    
	int Max_File_length;
	struct AFD *next;
}AFD,*AFD_ptr;


#define MaxDisk 512*1024   //一个扇区512字节,假设有1024个扇区,模拟磁盘的大小
int Max_User=10;
int Max_Open=5;
int Max_End=0;
UFD_ptr pufd=NULL;
MFD_ptr pmfd=NULL;
AFD_ptr pafd=NULL;
char User_name[30];   
char flag='n';
char Disk_Size[MaxDisk];    //最后在打印输出的时候，用RWX表示即可


typedef struct Disk_Table
{
	int Max_length;      //最大长度
	int Start;          //开始位置
}Disk_Node;
Disk_Node Disk_Head;

void Init_Disk()
{
	Disk_Head.Max_length=MaxDisk;
	Disk_Head.Start=0;
}

bool Init_MFD(){
    pmfd = (MFD *)new MFD;
    MFD *p = pmfd;
    ifstream ifs("MFD.txt");
    if(!ifs){
        cerr<<"Error opening!\n";
        p->next=NULL;
        p->Ufd_next = NULL;
        return false;
    }
    while(!ifs.eof()){
        p->next = (MFD *)new MFD;
        ifs>>p->next->User_name>>p->next->User_passwd>>p->next->End;
        if(p->next->End>Max_End){
            Max_End=p->next->End;
        }
        p = p->next;
        p->Ufd_next =NULL;
        p->next=NULL;
    }
    ifs.close();
    return true;
}

void Print_UFD(){
    UFD *p =pufd->next;
    if(!p){
        puts("Sorry, this user didn't create any files, please create first!!!");
        return;
    }
    cout<<"FileName\t\tMaxFileLength\t\tPermission\t\tStartPos\t\tFileLength\n";
    while(p){
        cout<<p->File_name<<"\t\t"<<p->Max_File_length;
		if(p->Protect==0)
			cout<<"\t\t"<<"---";
		else if(p->Protect==1)
			cout<<"\t\t"<<"r-x";
		else if(p->Protect==2)
			cout<<"\t\t"<<"rwx";
		cout<<"\t\t"<<p->Start;
		cout<<"\t\t"<<p->File_length<<endl;
		p=p->next;
    }
}

bool Init_UFD(char *name){
    ifstream ifs(name);
    pufd = (UFD *)new UFD;
    UFD *p = pufd;
    char temp[MaxDisk];
    bool Index = false;
    if(!ifs){
        cerr<<"Error opening!\n";
        p->next = NULL;
        return false;
    }
    while(!ifs.eof()){
        memset(temp,'\0',sizeof(temp));
        p->next = (UFD *)new UFD;
        if(!Index){
            pmfd->Ufd_next=p->next;
            Index = true;
        }//???
        ifs>>p->next->File_name>>p->next->Max_File_length>>p->next->Protect>>p->next->Start>>p->next->File_length;
		ifs>>temp;
        if(temp[0]=='#')temp[0]='\0';//???
        for(int i=p->next->Start,j=1;j<=p->next->Max_File_length-1;i++,j++){
            Disk_Size[i]=temp[j-1];
            if(!Disk_Size[i])
				break;//???
        }
        Disk_Head.Max_length-=p->next->Max_File_length;//???
        p = p->next;
        p->next =NULL;
    }
    ifs.close();
    return true;
}

bool User_Check(){
    string User_passwd;
    while(1){
        puts("Please input username");
        cin>>User_name;
INIT:
        puts("Please input password");
        cin>>User_passwd;
        MFD *p = pmfd->next;
        char temp[30];
        memset(temp,'\0',sizeof(temp));
        strcpy(temp,User_name);
        while(p){
            if(User_name==p->User_name){
                if(User_passwd==p->User_passwd){
                    puts("Success Login!");
                    strcat(temp,".txt");
                    Init_UFD(temp);
                    Disk_Head.Start=Max_End;//???
                    return true;
                }else{
                    puts("Sorry,wrong password,please login again.");
                    goto INIT;
                }
            }
            p=p->next;
        }
        puts("User not found,please login again.");
    }
}

void Init_AFD(){
    pafd=(AFD *)new AFD;
    pafd->next=NULL;
}//???

bool Create_MFD(){
    string User_name;
    char User_passwd[30];
    MFD *p = pmfd;
    puts("Please enter the user name to create:");
    cin>>User_name;
    puts("password:");
    cin>>User_passwd;
    while(p){
        if(User_name==p->User_name){
            puts("This user name already exists!!!");
            return false;
        }
        if(!p->next)break;
        p = p->next;
    }
    p->next = (MFD *)new MFD;
    p = p->next;
    p->User_name = User_name;
    p->User_passwd = User_passwd;
    p->End = 0;
    p->next=NULL;
    p->Ufd_next= NULL;
    Max_User--;
    return true;
}

bool Create_UFD(){
    string File_name;
    UFD *p = pufd;
    unsigned int Protect;
    int Max_File_length;
    puts("Please enter the file name to create:");
    cin>>File_name;
    puts("Enter the type of file protection");
    puts("0:---,1:r-x,2:rwx");
    cin>>Protect;
    puts("Please enter the maximum capacity");
    cin>>Max_File_length;
    while(p){
        if(File_name==p->File_name){
            puts("This filename already exists!!!");
            return false;
        }
        if(!p->next)break;
        p=p->next;
    }
    p->next=(UFD *)new UFD;
    p=p->next;
    p->File_name=File_name;
    p->Max_File_length=Max_File_length;
    p->Start=Disk_Head.Start;//???
    p->File_length=0;
    Disk_Head.Start+=Max_File_length;
    p->next=NULL;
    return true;
}

bool Delete_UFD(){
    string File_name;
    puts("Please enter the file name to delete:");
    cin>>File_name;
    UFD *p = pufd,*temp;
    AFD *pa=pafd;
    while(p->next){
        if(File_name==p->next->File_name){
            puts("Sorry, the file has been opened, please close it first, and then delete it!!!");
            return false;
        }
    }
    while(p->next){
        if(File_name==p->next->File_name){
            temp=p->next;
            p->next=p->next->next;
            delete temp;
            puts("File deleted successfully!!!");
            return true;
        }
        p=p->next;
    }
    puts("Sorry, the file to be deleted does not exist!!!");
    return false;
}

bool Open(){
    string File_name;
    unsigned int Protect;
    puts("Please enter the file name to open:");
    cin>>File_name;
    UFD *p = pufd->next;
    AFD *pa = pafd->next;
    while(pa){
        if(File_name==pa->File_name){
            cout<<"File"<<File_name<<" already open!!!\n";
            return true;
        }
        if(!pa->next){
            break;
        }
        pa = pa->next;
    }
    if(!pa){
        pa = pafd;
    }
    while(p){
        if(File_name==p->File_name){
            if(!Max_Open){
               puts("Sorry, you can only open 5 files at most. Please close other open files before operation!!!");
               return false;
            }
            if(p->Protect==0){
                puts("Sorry, nothing can be done with this file!!!");
                return false;
            }
            puts("Please select how to open the file < 1-read-only, 2-read-write >");
            cin>>Protect;
            pa->next=(AFD *)new AFD;
            pa=pa->next;
            pa->File_name=p->File_name;
            pa->Start=p->Start;
            pa->File_length=p->File_length;
            pa->Max_File_length=p->Max_File_length;
            pa->Protect=Protect;
            if(Protect==1){
                pa->Pointer=0;//???
            }else{
                pa->Pointer=p->File_length;
            }
            pa->next=NULL;
            Max_Open--;
            cout<<"File"<<File_name<<"is open!!\n";
            return true;
        }
        p= p->next;
    }
    puts("Sorry, the file to be opened does not exist!!!");
    return false;
}

void Close(){
    string File_name;
    UFD *pu = pufd->next;
    puts("Please enter the file name to close:");
    cin>>File_name;
    AFD *p=pafd,*temp;
    while(p&&p->next){
        if(File_name==p->next->File_name){
            temp=p->next;
            p->next=p->next->next;
            if(temp->Protect==2){
                while(pu){
                    if(temp->File_name==pu->File_name){
                        pu->File_length=temp->File_length;
                        break;
                    }
                    pu=pu->next;
                }
            }
            delete temp;
            cout<<"File"<<File_name<<"is close!\n";
            return ;
        }
        p=p->next;
    }
    puts("Sorry, the file to be closed is not open!!!");
}

bool Read_File(){
    string File_name;
    unsigned int length;
    AFD *p=pafd->next;
    puts("Please enter the file name to read:");
    cin>>File_name;
    puts("Please enter the length:");
    cin>>length;
    while(p){
        if(File_name==p->File_name){
            for(int i=p->Start,j=1;j<=length;i++,j++){
                cout<<Disk_Size[i];//???
            }
            cout<<endl;
            cout<<"File"<<File_name<<" read successful\n";
            return true;
        }
        p= p->next;
    }
    puts("Failed to read. The file has not been opened!!!");
    return false;
}

bool Write_File(){
    string File_name;
    unsigned int length;
    AFD *p=pafd->next;
    char temp[MaxDisk]={'\0'};
    puts("Please enter the file name to write:");
    cin>>File_name;
    while(p){
        if(File_name==p->File_name){
            if(p->Protect!=2){
                cout<<"File"<<File_name<<"can not be written\n";
                return false;
            }
            puts("Please enter the length to write:");
            cin>>length;
            if(p->Pointer+=length<=p->Max_File_length){
                puts("Please write the content of the specified length: < end with carriage return >");
                cin.getline(temp,MaxDisk);
                for(int i=p->Start+p->File_length,j=1;j<=strlen(temp);i++,j++){
                    Disk_Size[i]=temp[j-1];//???
                }
                p->Pointer+=length;
                cout<<"File"<<File_name<<"write successfully!!!\n";
            }else{
                puts("The size of the data to be written overflows, which has exceeded the allocated capacity of the file. Writing failed!!!");
                return false;
            }
            return true;
        }
        p=p->next;
    }
    puts("Write failed, file has not been opened!!!");
    return false;
}

void Destroy_Space(){//???
    MFD *pm=pmfd;
    while(pm){
        pmfd=pmfd->next;
        delete pm;
        pm=pmfd;
    }
    AFD *pa=pafd;
    while(pa){
        pafd=pafd->next;
        delete pa;
        pa=pafd;
    }	
    UFD *pu=pufd;
	while(pu)
	{
		pufd=pufd->next;
		delete pu;
		pu=pufd;
	}
}

void Save_MFD(){
    ofstream ofs;
    ofs.open("MFD.txt");
    if(!ofs.is_open()){
        puts("The MFD can't open!!!");
        if(flag=='y'){
            puts("Saving home directory user name information");
        }else{
            ofs.close();
        }
    }
}

void Save_UFD(char *name){
    ofstream ofs;
    char temp[MaxDisk]={'\0'};
    ofs.open(name);
    if(!ofs.is_open()){
        cout<<"File"<<name<<"can't open!!!\n";
        ofs.close();
    }
    UFD *p = pufd->next;
    while(p){
        memset(temp,'\0',sizeof(temp));
        for(int i=p->Start,j=1;j<=p->Max_File_length;i++,j++){
            if(Disk_Size[i]){
                temp[j-1]=Disk_Size[i];
            }else{
                break;
            }
        }
        if(!temp[0]){
            temp[0]='#';
        }
        ofs<<p->File_name<<" "<<p->Max_File_length<<" "<<p->Protect<<" "<<p->Start<<" "<<p->File_length<<" "<<temp;
        if(p->next)
            ofs<<"\n";
        p=p->next;
    }
    ofs.close();
}

void Quit_System(){
    AFD *pa=pafd->next;
    UFD *pu=pufd->next;
    while(pa){
        if(pa->Protect==2){
            while(pu){
                if(pa->File_name==pu->File_name){
                    pu->File_length=pa->Pointer;
                    break;
                }
                pu=pu->next;
            }
        }
        pa=pa->next;
    }
    char temp[30];
    strcpy(temp,User_name);
    strcat(temp,".txt");
    Save_MFD();
    Save_UFD(temp);
    Print_UFD();
    Destroy_Space();
}

void Show(){
    puts("------------Secondary File System------------");
    puts("-                                           -");
    puts("-      login              logout            -");
    puts("-      create             delete            -");
    puts("-      read               write             -");
    puts("-      open               close             -");
    puts("-      help               quit              -");
    puts("-                                           -");
    puts("---------------------------------------------");
}

void System_Init(){
Start:
    Show();
    Init_Disk();
    if(!Init_MFD()){
        int num;
        puts("The home directory has not been created yet. Do you want to create it?  (y/n)");
        cin>>flag;
        puts("Please enter the number of user folders to create: (1-10)");
        cin>>num;
        if(flag=='y'){
            while(num--){
                Create_MFD();
                if(!Max_User){
                    puts("This system supports 10 users at most. Failed to create redundant users. Please delete other users and try again!!!");
                    return;
                }
            }
            Save_MFD();
            puts("The main directory has been created, and the user's directory has been saved. Do you want to continue?  (y/n)");
            cin>>flag;
            if(flag=='y'){
                goto Start;
            }
        }
    }
    return;
}

void File_System(){
    while(1){
        string cmd;
        puts("Please enter a command:  ");
        cin>>cmd;
        if(cmd=="login"){
            if(!User_Check()) break;
            Init_AFD();
        }
        else if(cmd=="logout"){
            puts("User log out successfully!!!");
            Quit_System();
            System_Init();
            File_System();
        }
        else if(cmd=="create") Create_UFD();
        else if(cmd=="delete") Delete_UFD();
        else if(cmd=="open") Open();
        else if(cmd=="close") Close();
        else if(cmd=="read") Read_File();
        else if(cmd=="write") Write_File();
        else if(cmd=="ls") Print_UFD();
        else{
            Show();
        }
    }
}

int main(){
    System_Init();
    File_System();
    return 0;
}

