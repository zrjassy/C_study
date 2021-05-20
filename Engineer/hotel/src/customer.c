#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"

#define CUSTOMER_FILE "customer.txt"

int write_customer(Customer *c)
{
    FILE *fp;
    fp = fopen(CUSTOMER_FILE, "a");
    if (fp == NULL)
    {
        perror("open roomfile fail\n");
        return 1;
    }
    fprintf(fp, "%-5d", c->roomID);
    fprintf(fp, "%-11s", c->name);
    fprintf(fp, "%-20s", c->IDchard);
    fprintf(fp, "%-5d", c->Inday);
    fprintf(fp, "%-5d", c->Outday);
    fprintf(fp, "%-5d", c->deposit);
    fprintf(fp, "%-5d", c->status);
    fclose(fp);
    return 0;
}

Customer *read_customer()
{
    Customer *head;
    Customer *p, *pold, *newNode;
    FILE *fp;
    fp = fopen(CUSTOMER_FILE, "r");
    if (fp == NULL)
    {
        perror("open room file fail");
        return NULL;
    }
    head = (Customer *)malloc(sizeof(Customer));
    memset(head, 0, sizeof(Customer));
    head->next = NULL;
    p = head;
    while (!feof(fp))
    {
        fscanf(fp, "%d", &p->roomID);
        fscanf(fp, "%s", p->name);
        fscanf(fp, "%d", p->IDchard);
        fscanf(fp, "%d", &p->Inday);
        fscanf(fp, "%d", &p->Outday);
        fscanf(fp, "%d", &p->deposit);
        fscanf(fp, "%d", &p->status);
        newNode = (Customer *)malloc(sizeof(Customer));
        memset(newNode, 0, sizeof(Customer));
        pold = p;
        p->next = newNode;
        p = newNode;
    }
    pold->next = NULL;
    free(p);
    fclose(fp);
    return head;
}

int free_customer(Customer *head)
{
    Customer *q;
    q=head;
    while (head != NULL)
    {
        head=head->next;
        free(q);
        q=head;
    }
    return 0;
}

// 返回用户选择的房间ID,并将用户信息写入文件中，后续嵌入账单管理，需要先打印出押金
int add_customer()
{
    int roomid;
    printf("please enter the choosed roomID:");
    scanf("%d",&roomid);

}

// 返回用户押金，写入失败返回0
// int add_i()
// {
//     ROOM *r;
//     r = (ROOM *)malloc(sizeof(ROOM));
//     printf("please input room id:");
//     scanf("%d", &r->ID);
//     getchar();
//     printf("please input room type:");
//     gets(r->Type);
//     printf("please input room price:");
//     scanf("%d", &r->price);
//     printf("please input room status:0-empty,1-not empty,2-not clean,3-cleaning:");
//     scanf("%d", &r->status);
//     r->next = NULL;
//     int i = write_room(r);
//     free(r);
//     if (i != 0)
//         return 0;
//     else
//         return 1;
// }

// 返回用户选择的房间ID,并将文件中的用户状态改变，后续嵌入账单管理，需要先打印出实际金额与押金的差值
int exit_customer()
{

}
