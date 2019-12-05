#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFER_SIZE 1024

/*
    笔记：📓
    🙋main（）函数参数的使用  main（int argc，char **argv）  
    argc代表参数的个数，
    argv为二级字符串指针，即为多个字符串数组，
    也就是说，argv[0]代表其第一个参数，argv[1]代表其第二个参数，
    arg[2]代表其第三个参数，以此类推
    🙋lseek（）函数的使用，
    第一个参数为文件描述符，
    第二个参数为偏移量，
    第三个参数（SEEK_CUR,SEEK_SET,SEEK_END）,返回值为当前位置到开头的字节数
*/
int main(int argc, char **argv){
    int source,backup;
    int file_len;
    int ret = 1;
    char buffer[BUFFER_SIZE];
    if(argc!=3){
        printf("argc not enough\n");
        exit(0);
    }
    if((source = open(argv[1],O_RDONLY|O_CREAT))==-1){
        printf("open %s failed!\n",argv[1]);
        exit(0);
    }
    if((backup = open(argv[2],O_WRONLY|O_CREAT))==0){
        printf("open %s failed!\n",argv[2]);
        exit(0);
    }
    file_len = lseek(source,0,SEEK_END);        //读出文件行数
    lseek(source,0,SEEK_SET);       //将文件指针放回文件起始位置
    while(ret){
        ret = read(source,buffer,BUFFER_SIZE);
        if(ret == -1){
            printf("read error!\n");
            exit(0);
        }
        write(backup,buffer,ret);
        file_len -= ret;
        bzero(buffer,BUFFER_SIZE);
    }
    close(source);
    close(backup);
    exit(0);
}

//https://blog.csdn.net/qq_33974167/article/details/82731661