#include <stdio.h>
#include <stdlib.h>
#define maxsize 1024
typedef int datatype;

typedef struct Stack
{
    datatype elements[maxsize];
    int Top;
} stack;

// 置空栈
stack *SetNullS(stack *S)
{
    S->Top = -1;
    return S;
}

// 判断栈是否为空
int EmptyS(stack *S)
{
    if (S->Top >= 0)
        return 0;
    else
        return 1;
}

// 进栈
stack *PushStackS(stack *S, int e)
{
    if (S->Top >= maxsize - 1)
    {
        printf("Stack Overflow\n");
        return NULL;
    }
    else
    {
        S->Top++;
        S->elements[S->Top] = e;
    }
    return S;
}

// 出栈
datatype *PopS(stack *S)
{
    datatype *ret;
    if(EmptyS(S))
    {
        printf("Stack underflow\n");
        return NULL;
    }
    else
    {
        S->Top--;
        ret = (datatype *)malloc(sizeof(datatype));
        *ret = S->elements[S->Top+1];
        return ret;
    }
}

stack *Create()
{
    stack *s;
    s=(stack *)malloc(sizeof(stack));
    s->Top=-1;
}

int main()
{
    /* code */
    stack *s;
    s=Create();
    s=PushStackS(s,1);
    s=PushStackS(s,4);
    s=PushStackS(s,2);
    s=PushStackS(s,7);
    int *x=PopS(s);
    printf("%d\n",*x);
    return 0;
}


