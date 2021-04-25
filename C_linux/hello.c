#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    int pid;
    pid = fork();
    printf("%d\n",pid);
}
