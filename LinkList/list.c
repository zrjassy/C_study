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
        scanf("%d", &node->score);
        end->next = node;
        end = node;
    }
    end->next = NULL;
    return head;
}

// 按序号查找节点
LinkList *Get(LinkList *head, int i)
{
    int j;
    LinkList *p;
    p = head;
    j = 0;
    while ((p->next != NULL) && (j < i))
    {
        p = p->next;
        j++;
    }
    if (i == j)
        return p;
    else
        return NULL;
}

// 按值查找节点的位置
LinkList *Locate(LinkList *head, int score)
{
    LinkList *p;
    p = head->next;
    while ((p != NULL) && (p->score != score))
        p = p->next;
    if (p == NULL)
        return NULL;
    else
        return p;
}

void Output(LinkList *head)
{
    while (head->next != NULL)
    {
        head = head->next;
        printf("%d\n", head->score);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    LinkList *head = Creat(n);
    // Output(head);
    LinkList *p1 = Get(head, 3);
    printf("%d\n", p1->score);
    LinkList *p2 = Locate(head, 15);
    printf("%p\n", p2);
    return 0;
}