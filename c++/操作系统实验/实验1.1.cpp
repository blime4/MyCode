#include<stdio.h>
#include<unistd.h>
using namespace std;
int main(){
    pid_t p1,p2;
    // p1 = fork();
    while((p1=fork())==-1);
    if(p1==0) putchar('b');
    else {
        while((p2=fork())==-1);
        if(p2==0) putchar('c');
        else putchar('a');
    }
    
}