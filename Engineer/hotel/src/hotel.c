#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hotel.h"
#include "customer.h"

#define ROOM_FILE "D:\\workstation\\C\\C_study\\Engineer\\hotel\\src\\room.txt"

int write_room(ROOM *r)
{
    FILE *fp;
    fp = fopen(ROOM_FILE, "a");
    if (fp == NULL)
    {
        perror("open roomfile fail\n");
        return 1;
    }
    fprintf(fp, "%-5d", r->ID);
    fprintf(fp, "%-10s", r->Type);
    fprintf(fp, "%-5d", r->status);
    fprintf(fp, "%-5d\n", r->price);
    fclose(fp);
    return 0;
}

ROOM *read_room()
{
    ROOM *head;
    ROOM *p, *pold, *newNode;
    FILE *fp;
    fp = fopen(ROOM_FILE, "r");
    if (fp == NULL)
    {
        perror("open room file fail");
        return NULL;
    }
    head = (ROOM *)malloc(sizeof(ROOM));
    memset(head, 0, sizeof(ROOM));
    head->next = NULL;
    p = head;
    while (!feof(fp))
    {
        fscanf(fp, "%d", &p->ID);
        fscanf(fp, "%s", p->Type);
        fscanf(fp, "%d", &p->status);
        fscanf(fp, "%d", &p->price);
        newNode = (ROOM *)malloc(sizeof(ROOM));
        memset(newNode, 0, sizeof(ROOM));
        pold = p;
        p->next = newNode;
        p = newNode;
    }
    pold->next = NULL;
    free(p);
    fclose(fp);
    return head;
}

int change_room(int roomid, int status)
{
    ROOM *head, *p;
    head = read_room();
    p = head;
    int t = 0;
    while (p != NULL)
    {
        if (p->ID == roomid)
        {
            t++;
            printf("\t\t\t  %-5d %-10s %-5d %-5d\n", p->ID, p->Type, p->status, p->price);
            p->status = status;
        }
        p = p->next;
    }
    if (t == 0)
        printf("none.\n");
    free_room(head);
}

int free_room(ROOM *head)
{
    ROOM *q;
    q = head;
    while (head != NULL)
    {
        head = head->next;
        free(q);
        q = head;
    }
    return 0;
}

int find_room(ROOM *r)
{
    ROOM *head;
    head = read_room();
    int option;
    if (r->price != -1)
        option = 1;
    else if (r->Type[0] != 'N')
        option = 2;
    else
        option = 3;
    switch (option)
    {
    case 1:
        find_room_by_price(head, r->price);
        break;
    case 2:
        find_room_by_type(head, r->Type);
        break;
    default:
        printf("NONE\n");
        break;
    }
    printf("enter anything to continue...");
    getchar();
    free_room(head);
    return 0;
}

int find_room_by_price(ROOM *head, int price)
{
    ROOM *p;
    p = head;
    int t = 0;
    printf("\t\t\t  the room with price:%5d\n", price);
    while (p != NULL && p->status == 0)
    {
        if (p->price == price)
        {
            t++;
            printf("\t\t\t  %-5d %-10s %-5d %-5d\n", p->ID, p->Type, p->status, p->price);
        }
        p = p->next;
    }
    if (t == 0)
        printf("none.\n");
}

int find_room_by_type(ROOM *head, char *type)
{
    ROOM *p;
    p = head;
    int t = 0;
    printf("\t\t\t  the room with type %10s\n", type);
    while (p != NULL && p->status == 0)
    {
        if (p->Type[0] == type[0])
        {
            t++;
            printf("\t\t\t  %-5d %-10s %-5d %-5d\n", p->ID, p->Type, p->status, p->price);
        }
        p = p->next;
    }
    if (t == 0)
        printf("none.\n");
}

int add_room()
{
    ROOM *r;
    r = (ROOM *)malloc(sizeof(ROOM));
    printf("please input room id:");
    scanf("%d", &r->ID);
    getchar();
    printf("please input room type:");
    gets(r->Type);
    printf("please input room price:");
    scanf("%d", &r->price);
    printf("please input room status:0-empty,1-not empty,2-not clean,3-cleaning:");
    scanf("%d", &r->status);
    r->next = NULL;
    int i = write_room(r);
    free(r);
    if (i != 0)
        return 0;
    else
        return 1;
}

int price_menu()
{
    system("cls");
    printf("\t\t\t      price\n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t      1 : 200\n");
    printf("\t\t\t      2 : 300\n");
    printf("\t\t\t      0 : exit\n");
    printf("\t\t\t===============================\n");
    printf("please select:");
    int c;
    scanf("%d", &c);
    while (c < 0 || c > 2)
    {
        printf("error,input again:");
        scanf("%d", &c);
    }
    int price;
    switch (c)
    {
    case 1:
        price = 200;
        break;
    case 2:
        price = 300;
        break;
    default:
        price = -1;
        break;
    }
    return price;
}

char *type_menu()
{
    system("cls");
    printf("\t\t\t      type\n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t      1 : one\n");
    printf("\t\t\t      2 : two\n");
    printf("\t\t\t      0 : exit\n");
    printf("\t\t\t===============================\n");
    printf("please select:");
    int c;
    scanf("%d", &c);
    while (c < 0 || c > 2)
    {
        printf("error,input again:");
        scanf("%d", &c);
    }
    char *Type;
    Type = (char *)malloc(10);
    switch (c)
    {
    case 1:
        strcpy(Type, "one");
        break;
    case 2:
        strcpy(Type, "two");
        break;
    default:
        strcpy(Type, "NONE");
        break;
    }
    return Type;
}

ROOM *InputMenu()
{
    ROOM *r = NULL;
    r = (ROOM *)malloc(sizeof(ROOM));
    memset(r, 0, sizeof(ROOM));
    strcpy(r->Type, "NONE");
    r->price = -1;
    int loop;
    int price;
    char *Type;
    char *s2;
    while (loop)
    {
        system("cls");
        printf("\t\t\t      	show free room\n");
        printf("\t\t\t===============================\n");
        printf("\t\t\t      1 : price\n");
        printf("\t\t\t      2 : type\n");
        printf("\t\t\t      0 : exit\n");
        printf("\t\t\t===============================\n");
        printf("please select:");
        int c;
        scanf("%d", &c);
        while (c < 0 || c > 2)
        {
            printf("error,input again:");
            scanf("%d", &c);
        }
        switch (c)
        {
        case 1:
            price = price_menu();
            if (price != -1)
            {
                r->price = price;
                loop = 0;
            }
            break;
        case 2:
            Type = type_menu();
            if (Type[0] != 'N')
            {
                strcpy(r->Type, Type);
                loop = 0;
            }
            break;
        default:
            loop = 0;
            break;
        }
    }
    return r;
}

int hotel_menu()
{
    printf("\t\t\t      	living managemant\n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t      1 : show free room\n");
    printf("\t\t\t      2 : choose room\n");
    printf("\t\t\t      3 : exit room\n");
    printf("\t\t\t      0 : exit\n");
    printf("\t\t\t===============================\n");
    printf("please select:");
    int c;
    scanf("%d", &c);
    while (c < 0 || c > 3)
    {
        printf("error,input again:");
        scanf("%d", &c);
    }
    return c;
}

void hotel_system()
{
    int c;
    int loop = 1;
    ROOM *r = NULL;
    int roomid;
    while (loop)
    {
        system("cls");
        c = hotel_menu();
        switch (c)
        {
        case 1:
            r = InputMenu();
            find_room(r);
            free(r);
            break;
        case 2:
            roomid=add_customer();
            change_room(roomid,1);
            break;
        case 3:
            roomid=exit_customer();
            change_room(roomid,0);
            break;
        default:
            loop = 0;
            break;
        }
    }
}
