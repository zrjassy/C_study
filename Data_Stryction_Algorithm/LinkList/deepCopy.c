#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
    struct Node *random;
} Node;

Node *Create()
{
    Node *Node1, *Node2, *Node3;
    Node1 = (Node *)malloc(sizeof(Node));
    Node2 = (Node *)malloc(sizeof(Node));
    Node3 = (Node *)malloc(sizeof(Node));
    Node1->val = 1;
    Node2->val = 2;
    Node3->val = 3;
    Node1->next = Node2;
    Node2->next = Node3;
    Node3->next = NULL;
    Node1->random = Node3;
    Node2->random = Node1;
    Node3->random = Node2;
    return Node1;
}

void Print(Node *L)
{
    while (L != NULL)
    {
        printf("%d ", L->val);
        L = L->next;
    }
    printf("\n");
}

Node *DeepCopy(Node *p)
{
    if (p == NULL)
        return p;
    Node *old = p;
    while (old != NULL)
    {
        Node *new_node;
        new_node = (Node *)malloc(sizeof(Node));
        new_node->val = old->val;
        new_node->next = old->next;
        old->next = new_node;  
        old = new_node->next;
    }
    old = p;
    while (old != NULL)
    {
        if (old->random != NULL)
            old->next->random = old->random->next;
        else
            old->next->random = NULL;
        old = old->next->next;
    }
    Node *old_list = p;
    Node *new_list = p->next;
    Node *newHead = p->next;
    while (old_list != NULL)
    {
        old_list->next = old_list->next->next;
        if (new_list->next != NULL)
            new_list->next = new_list->next->next;
        else
            new_list->next = NULL;
        old_list = old_list->next;
        new_list = new_list->next;
    }

    return newHead;
}

int main()
{
    Node *L1,*L2;
    L1 = Create();
    Print(L1);
    L2 = DeepCopy(L1);
    Print(L2);
    return 0;
}
