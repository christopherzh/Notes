#include<iostream>
#include<unistd.h>
#include<wait.h>
using namespace std;
int main(){
    pid_t p=fork();
    cout<<"This is a test!";
    cout<<getpid();
    wait(NULL);
    return 0;
}