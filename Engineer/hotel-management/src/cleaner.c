#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "room.h"
#include "recept.h"
#include "cleaner.h"

#define ROOM_FILE "room.txt"

int cleanerMenu()
{
	int c;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t==================================\n");
	printf("\t\t\t      Cleaner System\n");
	printf("\t\t\t      * 1 display room\n");
	printf("\t\t\t      * 2 clean room\n");
	printf("\t\t\t      * 3 edit personal information\n");
	printf("\t\t\t      * 0 quit\n");
	printf("\t\t\t==================================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>3)
	{
		printf("select error,again:");
		scanf("%d",&c);
	}

	return c;
}

int cleaner_seeroom()
{
	Room *p,*r,*head = read_room();
	int num =  1;
	int roomid;

	r = read_room();
	p = head;

	if(r == NULL)
	{
		getchar();
		printf("sorry,there is no room\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	printf("##########################\n");
	while(r->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,status:%d\n",num,r->roomId,r->type,r->status);
		r = r->next;
		num++;
	}
	getchar();
	printf("##########################\n");

	printf("which room you want to clean,please input roomId:\n");
	scanf("%d",&roomid);


	while(p != NULL)
	{
		if(p->roomId == roomid)
		{
			if(p->status != 2)
			{
				printf("sorry,input error\n");
				printf("press any key to continue.\n");
				getchar();
				return 0;
			}
			else if(p->status == 2)
			{
				p->status = 3;//0 empty,1 not empty,2 not clean,3 cleaning
				break;
			}
		}
		else     
			p = p->next;			
	}
 
	FILE *fp;
	fp = fopen(ROOM_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}

	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-10s",head->type);
		fprintf(fp,"%-5d",head->price);
		fprintf(fp,"%-5d",head->discount);
		fprintf(fp,"%-5d",head->cashPledge);
		fprintf(fp,"%-5d\n",head->status);

		//printf("%d\n",head->status);
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("display and choose room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


int cleanroom()
{
	int roomid,num = 1;
	FILE *fp;
	Room *r; //用来遍历room链表
	Room *p,*head = read_room();

	p = head;
	r = read_room();

	if(r == NULL)
	{
		getchar();
		printf("sorry,there is no room\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	printf("##########################\n");
	while(r->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,status:%d\n",num,r->roomId,r->type,r->status);
		r = r->next;
		num++;
	}
	getchar();
	printf("##########################\n");

	printf("which room is clean now,please input roomId:\n");
	scanf("%d",&roomid);

	while(p != NULL)
	{
		if(p->roomId == roomid)
		{
			if(p->status != 3)
			{
				printf("sorry,input error\n");
				printf("press any key to continue.\n");
				getchar();
				return 0;
			}
			else if(p->status == 3)
			{
				p->status = 0;//0 empty,1 not empty,2 not clean,3 cleaning
				break;
			}
		}
		else     
			p = p->next;			
	}


	fp = fopen(ROOM_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}

	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-10s",head->type);
		fprintf(fp,"%-5d",head->price);
		fprintf(fp,"%-5d",head->discount);
		fprintf(fp,"%-5d",head->cashPledge);
		fprintf(fp,"%-5d\n",head->status);
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("clean room success\n");
	printf("press any key to continue.\n");
	getchar();

	return 0;
}


void cleanerSystem(User *r)
{
	int c,loop=1;
	while(loop)
	{
		system("clear");
		printf("\n%s",r->name);  //左上角输出admin的名字
		//showTime(1);
		c = cleanerMenu();
		switch(c)
		{
			case 1:
				printf("display room\n");
				cleaner_seeroom();
				break;
			case 2:
				printf("clean room\n");
				cleanroom();
				break;
			case 3:
				printf("edit personal information\n");  //shanchu yonghu
				personalinformation(r);
				break;
			case 0:
			default:
				loop = 0;
				break;
		}
	}
}