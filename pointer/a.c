#include <stdio.h>

int main()
{
    int var = 10;
    int *p;
    p=&var;
    printf("var 变量的地址: %p\n", &var  );
    /* 在指针变量中存储的地址 */
    printf("p 变量存储的地址: %p\n", p );
    /* 使用指针访问值 */
    printf("*p 变量的值: %d\n", *p );
    return 0;
}