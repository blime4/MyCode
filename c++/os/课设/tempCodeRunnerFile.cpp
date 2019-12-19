extern int disk_block[10000];
// extern int disk_empty;

// typedef struct UFD{     //存储文件信息
//     string name;        //文件名
//     int attribute;      //属性
//     int length;         //长度
//     int a[10];          //为文件本身分配10个空间
//     int *p1;            //一级索引，100个空间
//     int (*p2)[100];     //二级索引，100*100个空间
//     struct UFD *next;
// }UFD;

// typedef struct DIR{
//     DIR *above;
//     string name;
//     int length;
//     DIR *next;
//     UFD *File_head;     //此目录下的文件指针
//     DIR *DIR_head;      //此目录下目录链表指针
// }DIR;

// class Cuse{             //定义管理用户目录的类
//     DIR *now;           //当前目录
//     UFD *Fhead;         //文件的头结点
//     DIR *Dhead;         //根目录的目录链头结点
//     string code;
//     string name;
//     int length;         //用户空间大小
//     int status;         //是否获得空间
// public:
//     void set_status(int);
//     int del_user();
//     int dis_file();     //显示文件所占外存块号
//     int dis_dir(DIR *d);//当前路径
//     int get_length();
//     string const *get_name();
//     string const *get_code();
//     int get_status();
//     int set_user(string,string);
//     DIR *get_now();
//     int del_file(UFD *f);
//     int del_dir(DIR *);
//     Cuse();
//     ~Cuse();
// 	int goback();				//返回上级
// 	int dis_now();				//显示当前目录
//     int new_file();
//     int new_dir();
// 	int open_dir();
// 	int open_file();
// 	int first_del_file();		//删除文件的前部分工作
// 	int first_del_dir();		//删除目录的前部分工作
// 	int set_code();
// };

// class Cdisk{            //用户类
// public:
//     Cuse user[10];
//     string code;
//     int dis_disk();
//     int first_del_file();
//     int del_user(int);
//     int new_user();
//     int set_code();
//     int login();
//     Cdisk();
//     virtual ~Cdisk(){};
// };


// int disk_block[10000];
// int disk_empty;

// // Cdisk::Cdisk(){
// //     string code = "12345678";
// //     for(int i=0; i<10000;i++){
// //         disk_block[i]=0;
// //     }
// //     disk_empty=10000;
// // }

// // int Cdisk::del_user(int i){
// //     Cuse C;
// //     C=user[i];
// //     user[i].del_user();
// //     return 1;
// // }
