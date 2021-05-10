#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch(L, X);
    printf("%d\n", P);

    return 0;
}

List ReadInput()
{
    int n;
    scanf("%d",&n);
    List L;
    L=(List)malloc(sizeof(List));
    L->Last=n;
    int i;
    for (i = 1; i < n+1; i++)
    {
        scanf("%d",&L->Data[i]);
    }
    return L;
}

/* 你的代码将被嵌在这里 */
Position BinarySearch(List L, ElementType X)
{
    int start = 1;
    int end = L->Last;
    while (start <= end)
    {
        int half = (end+start)/2;
        if(L->Data[half]==X)
        {
            return half;
        }
        else if (L->Data[half]>X) 
        {
            end = half - 1;
        } 
        else 
        {
            start = half + 1;
        }
    }
    return NotFound;
}