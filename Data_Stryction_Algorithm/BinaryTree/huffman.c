#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#define N 6
#define M 2 * N - 1

typedef char datatype;

typedef struct
{
    float weight;
    datatype data;
    int lchild, rchild, parent; // 取-1表示没有父亲或孩子
} hufmtree;

hufmtree tree[M];

#define EPS 1e-5

void Huffman(hufmtree tree[])
{
    int i,j,p1,p2;
    char ch;
    float small1,small2,f;
    for  (i = 0; i < M; i++)
    {
        tree[i].parent=-1;
        tree[i].lchild=-1;
        tree[i].rchild=-1;
        tree[i].weight=0.0;
        tree[i].data='0';
    }
    for (i = 0; i < N; i++)
    {
        scanf("%f",&f);
        tree[i].weight=f;
        scanf("%c",&ch);
        tree[i].data=ch;
    }
    for (i = N; i < M; i++)
    {
        p1=p2=0;
        small1=small2=FLT_MAX;
        for (j = 0; j < i; j++)
        {
            
        }
        
    }
    

}
