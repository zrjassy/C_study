#include <stdio.h>
#include <stdlib.h>
// #include<conio.h> linux中不支持此库

#define MAXSIZE 1024

typedef char datatype;
typedef struct
{
    datatype data[MAXSIZE];
    int last;
} sequenlist;
sequenlist *L;

// 建立顺序表L
sequenlist *Create()
{
    int i = 0;
    char ch;
    L = (sequenlist *)malloc(sizeof(sequenlist));
    L->last = -1;
    printf("Input:(end with #).\n");
    while ((ch = getchar()) != '#')
    {
        L->data[i++] = ch;
        L->last++;
    }
    return L;
}

// 将新节点X插入到顺序表L的第i个位置上去
int insert(sequenlist *L, char x, int i)
{
    int j;
    if ((L->last) >= (MAXSIZE - 1))
    {
        printf("overflow\n");
        return 0;
    }
    else if ((i < 1) || (i > (L->last) + 2))
    {
        printf("error\n");
        return 0;
    }
    else
    {
        for (j = L->last; j >= i - 1; j--)
            L->data[j + 1] = L->data[j];
        L->data[i - 1] = x;
        L->last = L->last + 1;
    }
    return 1;
}

// 删除某位置处的节点
int delete (sequenlist *L, int i)
{
    int j;
    if ((i < 1) || (i > L->last + 1))
    {
        printf("error\n");
        return 0;
    }
    else
    {
        for (j = i; j <= L->last; j++)
            L->data[j - 1] = L->data[j];
        L->last--;
    }
    return 1;
}

// 输出顺序表L中的内容
void Output(sequenlist *L)
{
    int i;
    printf("L:");
    for (i = 0; i <= L->last; i++)
        printf("%c", L->data[i]);
    printf("\n");
}

int main()
{
    char ch;
    int i, ret;
    L = Create();
    Output(L);
    // insert
    printf("insert:");
    scanf(" %c", &ch);
    printf("position:");
    scanf(" %d", &i);
    ret = insert(L, ch, i);
    if (ret)
        Output(L);
    // delete
    printf("deleteposition:");
    scanf(" %d", &i);
    ret = delete (L, i);
    if (ret)
        Output(L);
    return 0;
}