#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} LinkList;

LinkList *Creat(int n)
{
    LinkList *head, *node, *end;
    head = (LinkList *)malloc(sizeof(LinkList));
    end = head;
    for (int i = 0; i < n; i++)
    {
        node = (LinkList *)malloc(sizeof(LinkList));
        scanf(" %d", &node->data);
        end->next = node;
        end = node;
    }
    end->next = NULL;
    return head;
}

void Print(LinkList *L)
{
    while (L->next != NULL)
    {
        L = L->next;
        printf("%d ", L->data);
    }
    printf("\n");
}

LinkList *Reverse(LinkList *L)
{
    LinkList *A = NULL, *B = L->next;
    while (B != NULL)
    {
        LinkList *p = B->next;
        B->next = A;
        A = B;
        B = p;
    }
    return A;
}

int Circle(LinkList *L)
{
    LinkList *fast, *slow;
    fast = slow = L->next;
    while ((fast != NULL) && (fast->next != NULL))
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
            return 1;
    }
    return 0;
}

LinkList *Get(LinkList *head,int pos)
{
    int i=0;
    LinkList *p;
    p=head;
    // while ((p->next!=NULL) && (i<pos))
    // {
    //     p=p->next;
    //     i++;
    // }
    for(i=0;(p->next!=NULL) && (i<pos);i++)
        p=p->next;
    if(i==pos) return p;
    else return NULL;
    
}

int main()
{
    LinkList *L1;
    int n;
    scanf("%d", &n);
    L1 = Creat(n);
    LinkList *x=Get(L1,2);
    printf("%d\n",x->data);
    // L1 = Reverse(L1);
    // int x=Circle(L1);
    Print(L1);
    // printf("%d\n",x);
    return 0;
}
