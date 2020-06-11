#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>

using namespace std;

string indentifier[] ={"if","then","else","while","begin","do","end"};
string elseword[] ={"and","or","not"};

int main(){
    ifstream in;
    in.open(("./in.txt"));
    printf("<说明，种别编码，值>\n\n");
    string str="";
    char c;
    int num=0;
    while(in.get(c)){
        while(c == ' '){
            in.get(c);
        }
        if((c>='a'&&c<='z')||(c>='A'&&c<='Z')){
            while((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z')){
                str+=c;
                in.get(c);
            }
            for(int i=0; i<7;i++){
                if(str==indentifier[i]){
                    cout<<"<保留字,"<<i<<","<<str<<">"<<endl;
                    str="";
                }
            }
            for(int i=0; i<3;i++){
                if(str==elseword[i]){
                    cout<<"<"<<str<<","<<i+39<<","<<str<<">"<<endl;
                    str="";
                }
            }
            if(str!="")
                cout<<"<变量,56,"<<str<<">\n";
            str="";
        }
        else if((c>='0'&&c<='9')){
            num = 0;
            while(c>='0'&&c<='9'){
                num = num * 10 + c - '0';
                in.get(c);
            }
            cout<<"<整常量,"<<57<<","<<num<<">"<<endl;
        }
        else switch(c){
            case ':':
                in.get(c);
                if(c=='='){
                    cout<<"<赋值,38>\n";
                }
                break;
            case '+':
                cout<<"<+,34>\n";
                break;
            case '*':
                cout<<"<*,36>\n";
                break;   
            case '(':
                cout<<"<(,48>\n";
                break;  
            case ')':
                cout<<"<),49>\n";
                break;  
            case ';':
                cout<<"<;,8>\n";
                break;  
            case '#':   
                cout<<"<#,10>\n";
                break;        
        }
    }
}