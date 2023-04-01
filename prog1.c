#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
    printf("hello world");
    fork();
    return 0;
}