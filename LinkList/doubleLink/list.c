#include "list.h"
#include <stdlib.h>

dList *Create()
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    p->next = p;
    p->pre = p;
    dList *List;
    List->counter = 0;
    List->head = p;
    List->tail = p;
    return List;
}

dList *Insert(dList *List, int pos, int data)
{
    if(pos==0)
    {
        Node *p,*q;
        p=List->head;
        q=List->tail;

        Node *new;
        new = (Node *)malloc(sizeof(Node));
        new->data=data;
        new->next=q;
        new->pre=p;
        p->next=new;
        q->pre=new;
        List->counter++;
    }
    
}
dList *Delete(dList *List, int pos);
dList *Get(dList *List, int pos);
dList *Replace(dList *List, int pos, int data);
int *Has(dList *List, int data);