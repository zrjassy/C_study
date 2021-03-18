#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int score;
    struct student *next;
} LinkList;

LinkList *Creat(int n)
{
    LinkList *head, *node, *end;
    head = (LinkList *)malloc(sizeof(LinkList));
    end = head;
    for (int i = 0; i < n; i++)
    {
        node = (LinkList *)malloc(sizeof(LinkList));
        scanf(" %d", &node->score);
        end->next = node;
        end = node;
    }
    end->next = NULL;
    return head->next;
}

void Print(LinkList *L)
{
    while (L != NULL)
    {
        printf("%d ", L->score);
        L = L->next;
    }
    printf("\n");
}

LinkList *Reverse(LinkList *L)
{
    LinkList *A = NULL, *B = L;
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
    LinkList *fast,*slow;
    fast=slow=L;
    while((fast!=NULL)&&(fast->next!=NULL))
    {
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow)
            return 1;
    }
    return 0;
}

int main()
{
    LinkList *L1;
    int n;
    scanf("%d", &n);
    L1 = Creat(n);
    L1 = Reverse(L1);
    int x=Circle(L1);
    Print(L1);
    printf("%d\n",x);
    return 0;
}
