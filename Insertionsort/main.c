#include<stdio.h>

void dist(int n){
    int i=0;
    for(i=0;i<n;i++){
        printf("the %d out\n",i);
    }
}

int main(){
    int x=10;
    int test=10;
    dist(test);
    return 0;
}
