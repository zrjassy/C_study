#include<stdio.h>
#include<stdlib.h>
#include <string.h>

char *malloc_l(char *head,int len)
{
    char *p;
    p=(char *)malloc(sizeof(char)*(len+1));
    memset(p,'\0',sizeof(char)*(len+1));
    int i;
    for (i = 0; i<len; i++)
    {
        p[i]=head[i];
    }
    return p;
}

int main(int argc, char const *argv[])
{
    char p[10]="helloworld";
    char *s;
    s=malloc_l(p,10);
    printf("%s\n",s);
    s=malloc_l(p,10);
    printf("%s",s);
    return 0;
}
