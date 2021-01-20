#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    int score;
    struct student *next;
} LinkList;

LinkList *creat(int n)
{
    LinkList *head, *node, *end;
    head = (LinkList*)malloc(sizeof(LinkList));
    end=head;
    for(int i=0;i<n;i++){
        node=(LinkList*)malloc(sizeof(LinkList));
        scanf("%d",&node->score);
        end->next=node;
        end=node;
    } 
    end->next=NULL;
    return head;
}

int main(){
    int n;
    scanf("%d",&n);
    LinkList *head = creat(n);

    while(head->next !=NULL)
    {
        head = head->next;
        printf("%d\n",head->score);
    }
    return 0;
}