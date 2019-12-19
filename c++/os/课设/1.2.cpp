#include<bits/stdc++.h>

#define MEM_D_SIZE 1024*1024    //总磁盘空间为1M
#define DISKSIZE 1024			//磁盘块的大小1K
#define DISK_NUM 1024			//磁盘块数目1K
#define FATSIZE  DISK_NUM*sizeof(struct fatitem)	//FAT表大小
#define ROOT_DISK_NO FATSIZE/DISKSIZE+1				//根目录起始盘块号
#define ROOT_DISK_SIZE sizeof(struct direct)		//根目录大小
#define DIR_MAXSIZE  1024		//路径最大长度为1KB
#define MSD   5					//最大子目录数5
#define MOFN  5					//最大文件深度为5
#define MAX_WRITE 1024*128		//最大写入文字长度128KB  

struct fatitem  /* size 8*/ 
{ 
	int item;  /*存放文件下一个磁盘的指针*/ 
	char em_disk; /*磁盘块是否空闲标志位 0 空闲*/ 
}; 

struct direct  
{ 
	/*-----文件控制快信息-----*/ 
	struct FCB 
	{ 
		char name[9];  /*文件/目录名 8位*/ 
		char property;  /*属性 1位目录 0位普通文件*/ 
		int size;   /*文件/目录字节数、盘块数)*/ 
		int firstdisk;  /*文件/目录 起始盘块号*/ 
		int next;   /*子目录起始盘块号*/ 
		int sign;   /*1是根目录 0不是根目录*/ 
		
	}directitem[MSD+2]; 
	
}; 

struct opentable  
{ 
	struct openttableitem  
	{ 
		char name[9]; /*文件名*/ 
		int firstdisk; /*起始盘块号*/  
		int size;  /*文件的大小*/ 
	}openitem[MOFN]; 
	int cur_size;  /*当前打文件的数目*/ 
}; 

struct fatitem *fat;   /*FAT表*/ 
struct direct *root;   /*根目录*/ 
struct direct *cur_dir;   /*当前目录*/ 
struct opentable u_opentable; /*文件打开表*/ 
int  fd=-1;     /*文件打开表的序号*/ 
char *bufferdir;    /*记录当前路径的名称*/ 
char *fdisk;     /*虚拟磁盘起始地址*/ 

void initfile(); 
void   format(); 
void enter(); 
void     halt(); 
int create(char *name); 
int   open(char *name); 
int  close(char *name); 
int write(int fd,char *buf,int len); 
int  read(int fd,char *buf); 
int   del(char *name); 
int mkdir(char *name); 
int rmdir(char *name); 
void dir(); 
int cd(char *name); 
void print(); 
void show(); 

void initfile() 
{ 
	fdisk = (char *)malloc(MEM_D_SIZE*sizeof(char)); /*申请 1M空间*/ 
	format(); 
	
} 

void format() 
{ 
	int i; 
	FILE *fp; 
	
	fat = (struct fatitem *)(fdisk+DISKSIZE); /*计算FAT表地址，引导区向后偏移 1k)*/ 
	/*-----初始化FAT表------------*/ 
	fat[0].item=-1;  /*引导块*/ 
	fat[0].em_disk='1'; 
	
	for(i=1;i<ROOT_DISK_NO-1;i++) /*存放 FAT表的磁盘块号*/ 
	{ 
		fat[i].item=i+1; 
		fat[i].em_disk='1';   
	} 
	
	fat[ROOT_DISK_NO].item=-1;  /*存放根目录的磁盘块号*/ 
	fat[ROOT_DISK_NO].em_disk='1'; 
	
	for(i=ROOT_DISK_NO+1;i<DISK_NUM;i++) 
	{ 
		fat[i].item = -1; 
		fat[i].em_disk = '0';   
	} 
	/*-----------------------------------------------*/ 
	root = (struct direct *)(fdisk+DISKSIZE+FATSIZE); /*根目录的地址*/ 
	/*初始化目录*/ 
	/*---------指向当前目录的目录项---------*/ 
	root->directitem[0].sign = 1; 
	root->directitem[0].firstdisk = ROOT_DISK_NO; 
	strcpy(root->directitem[0].name,"."); 
	root->directitem[0].next = root->directitem[0].firstdisk; 
	root->directitem[0].property = '1'; 
	root->directitem[0].size = ROOT_DISK_SIZE; 
	/*-------指向上一级目录的目录项---------*/ 
	root->directitem[1].sign = 1; 
	root->directitem[1].firstdisk = ROOT_DISK_NO; 
	strcpy(root->directitem[1].name,".."); 
	root->directitem[1].next = root->directitem[0].firstdisk; 
	root->directitem[1].property = '1'; 
	root->directitem[1].size = ROOT_DISK_SIZE; 
	if((fp = fopen("disk.dat","wb"))==NULL) 
	{ 
		printf("Error:\n Cannot open file \n"); 
		return; 
	} 
	for(i=2;i<MSD+2;i++) /*-子目录初始化为空-*/ 
	{ 
		root->directitem[i].sign = 0; 
		root->directitem[i].firstdisk = -1; 
		strcpy(root->directitem[i].name,""); 
		root->directitem[i].next = -1; 
		root->directitem[i].property = '0'; 
		root->directitem[i].size = 0;   
	} 
	
	
	if((fp = fopen("disk.dat","wb"))==NULL) 
	{ 
		printf("Error:\n Cannot open file \n"); 
		return; 
	} 
	if(fwrite(fdisk,MEM_D_SIZE,1,fp)!=1) /*把虚拟磁盘空间保存到磁盘文件中*/   
	{ 
		printf("Error:\n File write error! \n"); 
	} 
	
	fclose(fp);   
	
} 
void enter() 
{ 
	FILE *fp; 
	int i; 
	
	fdisk = (char *)malloc(MEM_D_SIZE*sizeof(char)); /*申请 1M空间*/ 
	if((fp=fopen("disk.dat","rb"))==NULL) 
	{ 
		printf("Error:\nCannot open file\n"); 
		return;                                 
	} 
	if(!fread(fdisk,MEM_D_SIZE,1,fp))  /*把磁盘文件disk.dat 读入虚拟磁盘空间(内存)*/     
	{ 
		printf("Error:\nCannot read file\n"); 
		exit(0);   
	} 
	fat = (struct fatitem *)(fdisk+DISKSIZE);  /*找到FAT表地址*/ 
	root = (struct direct *)(fdisk+DISKSIZE+FATSIZE);/*找到根目录地址*/ 
	fclose(fp); 
	/*--------------初始化用户打开表------------------*/ 
	for(i=0;i<MOFN;i++) 
	{ 
		strcpy(u_opentable.openitem[i].name,""); 
		u_opentable.openitem[i].firstdisk = -1; 
		u_opentable.openitem[i].size = 0;               
	} 
	u_opentable.cur_size = 0; 
	
	cur_dir = root; /*当前目录为根目录*/ 
	bufferdir = (char *)malloc(DIR_MAXSIZE*sizeof(char)); 
	strcpy(bufferdir,"Root:");  
}

void halt() 
{ 
	FILE *fp; 
	int i; 
	
	if((fp=fopen("disk.dat","wb"))==NULL) 
	{ 
		printf("Error:\nCannot open file\n"); 
		return;                                 
	} 
	if(!fwrite(fdisk,MEM_D_SIZE,1,fp)) /*把虚拟磁盘空间(内存)内容读入磁盘文件disk.dat */ 
	{ 
		printf("Error:\nFile write error!\n"); 
	} 
	fclose(fp); 
	
	free(fdisk); 
	free(bufferdir); 
	return;
}

int create(char *name) 
{ 
	
    int i,j; 
	
    if(strlen(name)>8) /*文件名大于 8位*/ 
		return(-1); 
	
    for(j=2;j<MSD+2;j++) /*检查创建文件是否与已存在的文件重名*/ 
    { 
		if(!strcmp(cur_dir->directitem[j].name,name)) 
			break;    
    } 
	if(j<MSD+2)     /*文件已经存在*/ 
		return(-4); 
	
    for(i=2;i<MSD+2;i++) /*找到第一个空闲子目录*/ 
    { 
		if(cur_dir->directitem[i].firstdisk==-1) 
			break;              
    }  
    if(i>=MSD+2) /*无空目录项*/ 
		return(-2); 
    if(u_opentable.cur_size>=MOFN) /*打开文件太多*/ 
		return(-3);  
    
	
    for(j=ROOT_DISK_NO+1;j<DISK_NUM;j++) /*找到空闲盘块 j 后退出*/ 
    { 
		if(fat[j].em_disk=='0') 
			break; 
    } 
	if(j>=DISK_NUM) 
		return(-5); 
    fat[j].em_disk = '1';  /*将空闲块置为已经分配*/ 
    /*-----------填写目录项-----------------*/ 
    strcpy(cur_dir->directitem[i].name,name); 
    cur_dir->directitem[i].firstdisk = j; 
    cur_dir->directitem[i].size = 0; 
    cur_dir->directitem[i].next = j; 
    cur_dir->directitem[i].property = '0'; 
    /*---------------------------------*/ 
    fd = open(name); 
    return 0; 
	
} 

int open(char *name) 
{ 
    int i, j; 
	
    for(i=2;i<MSD+2;i++) /*文件是否存在*/ 
    { 
		if(!strcmp(cur_dir->directitem[i].name,name)) 
			break;    
    }  
    if(i>=MSD+2) 
		return(-1); 
	/*--------是文件还是目录-----------------------*/   
	if(cur_dir->directitem[i].property=='1')
		return(-4); 
	
    /*--------文件是否打开-----------------------*/         
    for(j=0;j<MOFN;j++) 
    { 
		if(!strcmp(u_opentable.openitem[j].name,name)) 
			break; 
    }  
	if(j<MOFN)  /*文件已经打开*/ 
		return(-2); 
	
	
    if(u_opentable.cur_size>=MOFN) /*文件打开太多*/ 
		return(-3);  
	
    /*--------查找一个空闲用户打开表项-----------------------*/     
    for(j=0;j<MOFN;j++) 
    { 
		if(u_opentable.openitem[j].firstdisk==-1) 
			break;     
    } 
    /*--------------填写表项的相关信息------------------------*/ 
    u_opentable.openitem[j].firstdisk = cur_dir->directitem[i].firstdisk; 
    strcpy(u_opentable.openitem[j].name,name); 
    u_opentable.openitem[j].size = cur_dir->directitem[i].size; 
    u_opentable.cur_size++; 
    /*----------返回用户打开表表项的序号--------------------------*/ 
    return(j); 
} 

int close(char *name) 
{ 
    int i; 
	
    for(i=0;i<MOFN;i++) 
    { 
		if(!strcmp(u_opentable.openitem[i].name,name)) 
			break;    
    }  
    if(i>=MOFN)    
		return(-1);  
    /*-----------清空该文件的用户打开表项的内容---------------------*/ 
    strcpy(u_opentable.openitem[i].name,""); 
    u_opentable.openitem[i].firstdisk = -1; 
    u_opentable.openitem[i].size = 0; 
    u_opentable.cur_size--; 
	
	
    return 0; 
} 

int write(int fd, char *buf, int len) 
{ 
	char *first; 
	int item, i, j, k; 
	int ilen1, ilen2, modlen, temp; 
	/*----------用 $ 字符作为空格 # 字符作为换行符-----------------------*/ 
	char Space = 32;  
	char Endter= '\n'; 
	
	for(i=0;i<len;i++) 
	{ 
		if(buf[i] == '$') 
			buf[i] = Space; 
		else if(buf[i] == '#') 
			buf[i] = Endter; 
	} 
	
	/*----------读取用户打开表对应表项第一个盘块号-----------------------*/ 
	
	item = u_opentable.openitem[fd].firstdisk; 
	
	/*-------------找到当前目录所对应表项的序号-------------------------*/ 
	for(i=2;i<MSD+2;i++) 
	{ 
		if(cur_dir->directitem[i].firstdisk==item) 
			break; 
	} 
	temp = i; /*-存放当前目录项的下标-*/ 
	/*------找到的item 是该文件的最后一块磁盘块-------------------*/ 
	while(fat[item].item!=-1)  
	{ 
		item =fat[item].item; /*-查找该文件的下一盘块--*/ 
	} 
	
	/*-----计算出该文件的最末地址-------*/ 
	first = fdisk+item*DISKSIZE+u_opentable.openitem[fd].size%DISKSIZE; 
	
	/*-----如果最后磁盘块剩余的大小大于要写入的文件的大小-------*/ 
	if(DISKSIZE-u_opentable.openitem[fd].size%DISKSIZE>len) 
	{ 
		strcpy(first,buf); 
		u_opentable.openitem[fd].size = u_opentable.openitem[fd].size+len; 
		cur_dir->directitem[temp].size = cur_dir->directitem[temp].size+len; 
	} 
	else 
	{ 
		for(i=0;i<(DISKSIZE-u_opentable.openitem[fd].size%DISKSIZE);i++) 
		{/*写一部分内容到最后一块磁盘块的剩余空间(字节)*/  
			first[i] = buf [i]; 
		} 
		/*-----计算分配完最后一块磁盘的剩余空间(字节) 还剩下多少字节未存储-------*/ 
		ilen1 = len-(DISKSIZE-u_opentable.openitem[fd].size%DISKSIZE); 
		ilen2 = ilen1/DISKSIZE;   
		modlen = ilen1%DISKSIZE; 
		if(modlen>0) 
			ilen2 = ilen2+1; /*--还需要多少块磁盘块-*/ 
		
		for(j=0;j<ilen2;j++) 
		{ 
			for(i=ROOT_DISK_NO+1;i<DISK_NUM;i++)/*寻找空闲磁盘块*/ 
			{ 
				if(fat[i].em_disk=='0') 
					break; 
			} 
			if(i>=DISK_NUM) /*--如果磁盘块已经分配完了-*/ 
				return(-1); 
			first = fdisk+i*DISKSIZE; /*--找到的那块空闲磁盘块的起始地址-*/ 
			if(j==ilen2-1) /*--如果是最后要分配的一块-*/ 
			{ 
				for(k=0;k<len-(DISKSIZE-u_opentable.openitem[fd].size%DISKSIZE)-j*DISKSIZE;k++) 
					first[k] = buf[k]; 
			} 
			else/*-如果不是要最后分配的一块--*/ 
			{ 
				for(k=0;k<DISKSIZE;k++) 
					first[k] =buf[k]; 
			} 
			
			fat[item].item = i;  /*--找到一块后将它的序号存放在上一块的指针中-*/ 
			fat[i].em_disk = '1'; /*--置找到的磁盘快的空闲标志位为已分配-*/ 
			fat[i].item = -1;  /*--它的指针为 -1 (即没有下一块)-*/ 
		} 
		/*--修改长度-*/ 
		u_opentable.openitem[fd].size = u_opentable.openitem[fd].size+len; 
		cur_dir->directitem[temp].size = cur_dir->directitem[temp].size+len; 
	} 
	return 0; 
} 

int read(int fd, char *buf) 
{ 
	int len = u_opentable.openitem[fd].size; 
	char *first; 
	int i, j, item; 
	int ilen1, modlen; 
	
	item = u_opentable.openitem[fd].firstdisk; 
	
	
	ilen1 = len/DISKSIZE; 
	modlen = len%DISKSIZE; 
	if(modlen!=0) 
		ilen1 = ilen1+1; /*--计算文件所占磁盘的块数-*/ 
	
	first = fdisk+item*DISKSIZE; /*--计算文件的起始位置-*/ 
	
	for(i=0;i<ilen1;i++) 
	{ 
		if(i==ilen1-1) /*--如果在最后一个磁盘块-*/ 
		{ 
			for(j=0;j<len-i*DISKSIZE;j++) 
				buf[i*DISKSIZE+j] = first[j]; 
		} 
		else /*--不在最后一块磁盘块-*/ 
		{ 
			for(j=0;j<len-i*DISKSIZE;j++) 
				buf[i*DISKSIZE+j] = first[j]; 
			item = fat[item].item; /*-查找下一盘块-*/ 
			first = fdisk+item*DISKSIZE; 
		} 
	} 
	return 0; 
} 

int del(char *name) 
{ 
	int i,cur_item,item,temp; 
	
	for(i=2;i<MSD+2;i++) /*--查找要删除文件是否在当前目录中-*/ 
	{ 
		if(!strcmp(cur_dir->directitem[i].name,name)) 
			break; 
	}
} 

