#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Lnode
{
    int startaddress;
    int size;
    int state;
    struct Lnode *next;
} LNode;

LNode *initNode(LNode *p)
{
    if (p == NULL)
    {
        p = (LNode *)malloc(sizeof(LNode));
    }
    p->startaddress = 0;
    p->size = 128;
    p->state = 0;
    p->next = NULL;
    return p;
}

void printNode(LNode *p)
{
    printf(" -------------------------------------------------------\n");
    printf("| startaddress\tsize\tstate\t|\n");
    while (p != NULL)
    {
        if (p->state == 0)
        {
            printf("| %d\t\t%dKB\tfree\t|\n", p->startaddress, p->size);
        }
        else
        {
            printf("| %d\t\t%dKB\tbusy\t|\n", p->startaddress, p->size);
        }
        p = p->next;
    }
    printf(" -------------------------------------------------------\n");
}

void destory(LNode *p)
{
    LNode *q;
    q = p;
    while (p != NULL)
    {
        p = p->next;
        free(q);
        q = p;
    }
}

void showmenu()
{
    printf("1.malloc\n");
    printf("2.free\n");
    printf("3.show\n");
    printf("4.exit\n");
    printf("Input:");
}

LNode *fisrtmalloc(LNode *p, int size)
{
    LNode *head;
    head = p;
    while (p != NULL)
    {
        if (p->state == 0)
        {
            if (p->size > size)
            {
                // 剩余空间
                LNode *q;
                q = (LNode *)malloc(sizeof(LNode));
                q->startaddress = p->startaddress + size;
                q->size = p->size - size;
                q->state = 0;
                // 分配
                p->size = size;
                p->state = 1;
                // 改变链接
                q->next = p->next;
                p->next = q;
                break;
            }
            else if (p->size == size)
            {
                p->state = 1;
                break;
            }
        }
        if (p->next == NULL)
        {
            LNode *q;
            q = (LNode *)malloc(sizeof(LNode));
            q->startaddress = p->startaddress + p->size;
            q->size = size;
            q->state = 1;
            q->next = NULL;
            p->next = q;
            break;
        }
        p = p->next;
    }
    return head;
}

LNode *bestmalloc(LNode *p, int size)
{
    LNode *head;
    head = p;
    //最佳块指针
    LNode *q = NULL;
    int bestsize = 100000;
    // 遍历寻找最佳的空闲块
    while (p != NULL)
    {
        if (p->state == 0 && p->size >= size && p->size < bestsize)
        {
            q = p;
            bestsize = p->size;
            // break;
        }
        if(p->next!=NULL)
            p = p->next;
        else
            break;
    }
    // 如果遍历完q依旧为空则说明没有空闲区可以分配,直接分配在最后
    if (q == NULL)
    {
        q = (LNode *)malloc(sizeof(LNode));
        q->startaddress = p->startaddress + p->size;
        q->size = size;
        q->state = 1;
        q->next = NULL;
        p->next = q;
        return head;
    }
    if (q->size > size)
    { //最佳空闲块的大小大于需求大小
        //分配后剩余的空间
        // 剩余空间
        LNode *s;
        s = (LNode *)malloc(sizeof(LNode));
        s->startaddress = q->startaddress + size;
        s->size = q->size - size;
        s->state = 0;
        // 分配
        q->size = size;
        q->state = 1;
        // 改变链接
        s->next = q->next;
        q->next = s;
    }
    else if (q->size == size)
    {
        //最佳空闲块空间大小和需求相等
        q->state = 1;
    }
    return head;
}

LNode *myFree(LNode *p, int n)
{
    LNode *head;
    head = p;
    int i = 1;
    while (p != NULL)
    {
        if (p->state == 0 && p->next->state == 1 && i + 1 == n)
        {
            //释放空间的上一块空间空闲时
            p->size = p->size + p->next->size;
            LNode *q = p->next;
            p->next = q->next;
            free(q);
            if (p->next->state == 0)
            {
                //下一个空间是空闲空间时
                p->size = p->size + p->next->size;
                LNode *q = p->next;
                p->next = q->next;
                free(q);
            }
            break;
        }
        else if (p->state == 1 && i == n)
        {
            //释放空间和空闲空间不连续时
            p->state = 0;
            if (p->next != NULL && p->next->state == 0)
            {
                //下一个空间是空闲空间时
                p->size = p->size + p->next->size;
                LNode *q = p->next;
                p->next = q->next;
                free(q);
            }
            break;
        }
        else if (p->next == NULL)
        { //任务id不匹配时
            printf("error N\n");
            break;
        }
        p = p->next;
        i++;
    }
    return head;
}

int main(int argc, char const *argv[])
{
    LNode *head = NULL;
    head = initNode(head);
    printf("initialization.\n");
    printNode(head);
    int option;
    int action;
    while (1)
    {
        printf("please choose a method:\n 1.Fisrt method\n 2.Best method\n 3.exit\n");
        printf("Input:");
        scanf("%d", &option);
        if (option == 1 || option == 2)
        {
            while (1)
            {
                showmenu();
                scanf("%d", &action);
                if (action == 1 && option == 1)
                {
                    printf("Please input the size.\nInput:");
                    int size;
                    scanf("%d", &size);
                    head = fisrtmalloc(head, size);
                    printNode(head);
                }
                else if (action == 1 && option == 2)
                {
                    printf("Please input the size.\nInput:");
                    int size;
                    scanf("%d", &size);
                    head = bestmalloc(head, size);
                    printNode(head);
                }
                else if (action == 2)
                {
                    printf("Please input the free one.\nInput:");
                    int n;
                    scanf("%d", &n);
                    head = myFree(head, n);
                    printNode(head);
                }
                else if (action == 3)
                {
                    printNode(head);
                }
                else if (action == 4)
                {
                    destory(head);
                    head = NULL;
                    head = initNode(head);
                    break;
                }
                else
                {
                    printf("Error input!Please input again.\n");
                }
            }
        }
        else if (option == 3)
        {
            destory(head);
            break;
        }
        else
        {
            printf("Error input!Please input again.\n");
        }
    }
    return 0;
}
