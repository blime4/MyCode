#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int main(){
????char?*ptr1=(char*)malloc(10);
????char?*ptr2=(char*)malloc(10);
????memset(ptr1,'A',10);
????*(ptr1+10)='\0';
????printf("%x?%s\n",ptr1,ptr1);
????ptr2=(char*)realloc(ptr1,40960);
????printf("%x?%s\n",ptr2,ptr2);
}