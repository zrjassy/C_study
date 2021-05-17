#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hotel.h"
#include "customer.h"

#define ROOM_FILE "room.txt"


int write_room(ROOM *r)
{
    FILE *fp;
    fp = fopen(ROOM_FILE,"a");
    if(fp == NULL)
	{
		perror("open roomfile fail\n");
		return 1;
	}
    fprintf(fp,"%-5d",r->ID);  
	fprintf(fp,"%-10s",r->Type);
	fprintf(fp,"%-5d",r->status);
	fprintf(fp,"%-5d\n",r->price);
	fclose(fp);
	return 0;
}

int add_room()
{
    ROOM *r;
    r=(ROOM *)malloc(sizeof(ROOM));
    printf("please input room id:");
	scanf("%d",&r->ID);
	getchar();
	printf("please input room type:");
	// fgets(r->Type,9,stdin);
    gets(r->Type);
	//getchar();
	printf("please input room price:");
	scanf("%d",&r->price);   
	printf("please input room status:0-empty,1-not empty,2-not clean,3-cleaning:");
	scanf("%d",&r->status);
	//getchar();
	r->next = NULL;
    int i=write_room(r);
    free(r);
    if(i!=0)
        return 0;
    else
        return 1;
}

int hotel_menu()
{
	printf("\t\t\t      	住宿管理\n");
    printf("\t\t\t===============================\n");
    printf("\t\t\t      1 : 查看空闲房间\n");
    printf("\t\t\t      2 : 选择房间入住\n");
    printf("\t\t\t      3 : 退房\n");
    printf("\t\t\t      0 : 返回\n");
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
    while (loop)
    {
        system("cls");
        c=hotel_menu();
        switch(c)
		{
			case 1:
                find_room();
				break;
			case 2:
                add_customer();
                change_room();
				break;
            case 3:
                exit_customer();
                change_room();
				break;
			default:
				loop = 0;
				break;
		}
    }

}
