#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "room.h"
#include "recept.h"

int customerMenu()
{
	int c;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t==================================\n");
	printf("\t\t\t      Customer System\n");
	printf("\t\t\t      * 1 display room\n");
	printf("\t\t\t      * 2 show personal information\n");
	printf("\t\t\t      * 0 quit\n");
	printf("\t\t\t==================================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>2)
	{
		printf("select error,again:");
		scanf("%d",&c);
	}

	return c;
}

int findroom()
{
	Room *p;
	int num,x;
	p = read_room();
	if(p == NULL)
	{
		getchar();
		printf("there is no room,please go to add room\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}

	printf("which room do you want to display:1.All 2.single room 3.double room 4.kingbed room\n");
	scanf("%d",&x);

	if(x == 1)
	{
		num = 1;
		p = read_room();
		printf("##########################\n");
		while(p->next != NULL)
		{
			printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
				num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);
			p = p->next;
			num++;
		}
	}
	else if(x == 2)
	{
		num = 1;
		p = read_room();
		printf("##########################\n");
		while(p->next != NULL)
		{
			if(strcmp(p->type,"single") == 0)
			{
				printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
						num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);

				num++;
			}
			p = p->next;
		}
	}
	else if(x == 3)
	{
		num = 1;
		p = read_room();
		printf("##########################\n");
		while(p->next != NULL)
		{
			if(strcmp(p->type,"double") == 0)
			{
				printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
						num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);

				num++;
			}
			p = p->next;
		}
	}
	else if(x == 4)
	{
		num = 1;
		p = read_room();
		printf("##########################\n");
		while(p->next != NULL)
		{
			if(strcmp(p->type,"kingbed") == 0)
			{
				printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
						num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);

				num++;
			}
			p = p->next;
		}
	}
	else
	{
		getchar();
		printf("input error,please go back and choose again\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}


	getchar();
	printf("##########################\n");
	printf("show room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int cusself_informatin()
{
	Customer *p;
	char buf[19];
	int flag = 0;
	p = read_customer();

	printf("please input your personal ID:\n");
	scanf("%s",buf);

	printf("##########################\n");
	while(p->next != NULL)
	{
		if(strcmp(p->cusid,buf) == 0)
		{
			printf("roomId:%d\n Customer ID:%s\n Customer name:%s\n Customer age:%d\n Customer sex:%s\n Customer phone:%s\n Customer inDay:%s\n Customer outDay:%s\n status:%d\n",
			        p->roomId,p->cusid,p->cusname,p->cusage,p->cussex,p->phone,p->inDay,p->outDay,p->status);
			flag = 1;
			break;
		}
		p = p->next;
	}

	if(flag == 0)
	{
		getchar();
		printf("sorry,personal ID error,please go back and choose again\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}


	getchar();
	printf("##########################\n");
	printf("show information success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


void customerSystem()
{
	int c,loop=1;
	while(loop)
	{
		system("cls");
		//printf("\n%s",r->name);  //左上角输出admin的名字
		//showTime(1);
		c = customerMenu();
		switch(c)
		{
			case 1:
				printf("display room\n");
				findroom();
				break;
			case 2:
				printf("show personal information\n");  //shanchu yonghu
				cusself_informatin();
				break;
			case 0:
			default:
				loop = 0;
				break;
		}
	}
}