#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<iostream>

using namespace std;


int main(){
    puts("计科173谢绍波1706100109");
    int *string;
    string = (int *)malloc(10);
    if(string == NULL) printf("Insufficient memory available\n");
    else{
        printf("Memory space allocated for path name\n");
        cout<<"string="<<string<<endl;
        free(string);
        printf("Memory freed\n");
    }
    int *stringy;
    stringy = (int*)malloc(12);
    if(string==NULL){
        printf("Insufficient memory available\n");
    }else{
        printf("Memory space allocated for path name\n");
        cout<<"stringy="<<stringy<<endl;
        free(stringy);
        printf("Memory freed\n");
    }
}