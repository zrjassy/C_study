#include "list.h"
#include <stdlib.h>
#include <stdio.h>

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
    k = Get(List, pos);
    p = k->pre;
    q = k;
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = q;
    new_node->pre = p;
    p->next = new_node;
    q->pre = new_node;
    List->counter++;
    return List;
}

dList *Delete(dList *List, int pos)
{
    Node *p, *q; // 设置将要删除的节点的前后节点 如插入pos = 1 即在 0 和 原1之间插入
    Node *k;
    k = Get(List, pos);
    p = k->pre;
    q = k->next;
    free(k);
    p->next = q;
    q->pre = p;
    List->counter--;
    return List;
}

void Output(dList *List)
{
    Node *p;
    p = List->head;
    p = p->next;
    while (p != List->tail)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

Node *Get(dList *List, int pos)
{
    Node *k;
    if (pos * 2 <= List->counter)
    {
        k = List->head;
        for (int i = 0; i < pos; i++)
        {
            k = k->next;
        }
        k = k->next;
    }
    else
    {
        k = List->tail;
        for (int i = 0; i < List->counter - pos; i++)
        {
            k = k->pre;
        }
    }
    return k;
}

dList *Replace(dList *List, int pos, int data)
{
    Node *k;
    k=Get(List,pos);
    k->data = data;
    return List;
}

int Has(dList *List, int data)
{
    Node *p;
    p = List->head;
    p = p->next;
    while (p != List->tail)
    {
        if(p->data==data)
            return 1;
        p = p->next;
    }
    return 0;
}