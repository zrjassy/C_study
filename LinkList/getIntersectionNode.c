#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Linklist;

Linklist *getSameNode(Linklist *headA, Linklist *headB)
{
    if (headA == NULL || headB == NULL)
        return NULL;
    Linklist *pa, *pb;
    pa = headA;
    pb = headB;
    while (pa != pb)
    {
        pa = (pa == NULL) ? pb : pa->next;
        pb = (pb == NULL) ? pa : pb->next;
    }
    return pa;
}

int main()
{
    Linklist *Node1,*Node2,*Node3,*Node4;
    Node1 = (Linklist *)malloc(sizeof(Linklist));
    Node2 = (Linklist *)malloc(sizeof(Linklist));
    Node3 = (Linklist *)malloc(sizeof(Linklist));
    Node4 = (Linklist *)malloc(sizeof(Linklist));
    Node1->data=1;
    Node2->data=5;
    Node3->data=4;
    Node4->data=3;
    Node1->next=Node3;
    Node2->next=Node3;
    Node3->next=Node4;
    Node4->next=NULL;
    Linklist *p;
    p=getSameNode(Node1,Node2);
    printf("%d\n",p->data);
}
