#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    puts("计科173谢绍波1706100109");
    char buf;
    FILE *first,*first_bk;
    if((first = fopen("first.txt", "r")) == NULL){
        printf("Open fail!\n");
        exit(1);
    }
    if((first_bk = fopen("first_bk.txt","w"))==NULL){
        printf("Create fail!\n");
        exit(1);
    }
    while(fread(&buf,sizeof(buf),1,first)==1){
        if(fwrite(&buf,sizeof(buf),1,first_bk)==0){
            printf("Write fail!\n");
            exit(1);
        }
    }
    if(ferror(first)){
        printf("Read error!\n");
        exit(1);
    }
    else if(fclose(first)){
        printf("Close error!\n");
        exit(1);
    }
    else if(fclose(first_bk)){
        printf("Close error!\n");
        exit(1);
    }
    else printf("Copy succuss!\n");
}