#include<stdio.h>
#include<stdlib.h>

char *test(){
    char *arr = "hello world";
    return arr;
}

void test_(){
    char *s=test();
    printf("%s\n",s);
}

int main(){
    test_();
    return 0;
}