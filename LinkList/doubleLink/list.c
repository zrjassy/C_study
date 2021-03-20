#include "list.h"
#include <stdlib.h>

dList *Create()
{
    Node *p, *q;
    p = (Node *)malloc(sizeof(Node));
    q = (Node *)malloc(sizeof(Node));
    p->next = q;
    q->pre = p;
    dList *List;
    List = (dList *)malloc(sizeof(dList));
    List->counter = 0;
    List->head = p;
    List->tail = q;
    return List;
}

dList *Insert(dList *List, int pos, int data)
{
    Node *p, *q; // 设置将要插入的节点的前后节点 如插入pos = 1 即在 0 和 原1之间插入
    Node *k;
    if (pos * 2 <= List->counter)
    {
        k = List->head;
        for (int i = 0; i < pos; i++)
        {
            k = k->next;
        }
        p = k;
        q = k->next;
    }
    else
    {
        k = List->tail;
        for (int i = 0; i < List->counter - pos; i++)
        {
            k = k->pre;
        }
        p = k->pre;
        q = k;
    }
    Node *x;
    x = (Node *)malloc(sizeof(Node));
    x->data = data;
    x->next = q;
    x->pre = p;
    p->next = x;
    q->pre = x;
    List->counter++;
}
// dList *Delete(dList *List, int pos);
// dList *Get(dList *List, int pos);
// dList *Replace(dList *List, int pos, int data);
// int *Has(dList *List, int data);