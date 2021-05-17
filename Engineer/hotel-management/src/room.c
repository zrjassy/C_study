#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"
#include "room.h"

#define USER_FILE "user.txt"
#define ROOM_FILE "room.txt"

int write_room(Room *r)   //jia diyige
{
	FILE *fp;

	fp = fopen(ROOM_FILE,"a");
	if(fp == NULL)
	{
		perror("open roomfile fail\n");
		return 1;
	}
	fprintf(fp,"%-5d",r->roomId);  
	fprintf(fp,"%-10s",r->type);
	fprintf(fp,"%-5d",r->price);
	fprintf(fp,"%-5d",r->discount);
	fprintf(fp,"%-5d",r->cashPledge);
	fprintf(fp,"%-5d\n",r->status);  // zhuyi jia \n
	fclose(fp);
	return 0;
}

Room *read_room()
{
	Room *head;
	Room *p,*pold,*newNode;
	FILE *fp;
	fp = fopen(ROOM_FILE,"r");
	if(fp == NULL)
	{
		perror("open room file fail");
		return NULL;
	}
	head = (Room *)malloc(sizeof(Room));
	memset(head,0,sizeof(Room));  // malloc shenqingde kongjian qingling
	head->next = NULL;
	p = head;
	//pold = head;
	while(!feof(fp))  
	{
		fscanf(fp,"%d",&p->roomId);
		fscanf(fp,"%s",p->type);
		fscanf(fp,"%d",&p->price);
		fscanf(fp,"%d",&p->discount);
		fscanf(fp,"%d",&p->cashPledge);
		fscanf(fp,"%d",&p->status);

		newNode = (Room *)malloc(sizeof(Room));  //已经到最后一个了，但是还是 会创建出一个，导致多了一个，display的时候就会多出一行
		memset(newNode,0,sizeof(Room));
		pold = p;    //pold yonglai zhixiang p de qian yige
		p->next = newNode;
		p = newNode;
	}
	pold->next = NULL;  
	free(p);
	fclose(fp);
	return head;
}

int display_room()
{
	Room *p;
	int num =  1;
	p = read_room();
	if(p == NULL)
	{
		getchar();
		printf("there is no room,please go to add room\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	printf("##########################\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
			num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);
		p = p->next;
		num++;
	}
	getchar();
	printf("##########################\n");
	printf("show room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int add_room()    //tianjia zhihou hui xieru wenjian
{
	Room *pr;

	pr = (Room *)malloc(sizeof(Room));
	if(pr == NULL)
	{
		printf("malloc error\n");	
		return 1;
	}
	memset(pr,0,sizeof(Room));
	getchar();
	printf("please input room id:\n");
	scanf("%d",&pr->roomId);
	getchar();
	printf("please input room type:\n");
	fgets(pr->type,9,stdin);
	//getchar();
	printf("please input room price:\n");
	scanf("%d",&pr->price);
	//getchar();
	printf("please input discount of room:0-normal,1-sale\n");
	scanf("%d",&pr->discount);

	printf("please input cashPledge of the room:\n");
	scanf("%d",&pr->cashPledge); //yajin mo ren wei0
	//getchar();   
	printf("please input room status:0-empty,1-not empty,2-not clean,3-cleaning\n");
	scanf("%d",&pr->status);
	//getchar();
	pr->next = NULL;
	write_room(pr);
	free(pr);

	getchar();
	printf("Add room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int deleteroom()   //shanchu fangjian
{
	FILE *fp;
	Room *p,*pold; //用来遍历链表
	int flag = 0;
	int roomId;
	Room *head;
	head = read_room();
	pold = head;

	printf("which room do you want to delete,please input the roomId:\n");
	scanf("%d",&roomId);

	p = head;
	
	if(head == NULL)
	{
		printf("There is no room now,please go back add room.\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	if(head->roomId == roomId)  //删除首元节点
	{
		head = head->next;
		free(p);
		flag = 1;
	}
	else
	{
		while(p != NULL)
		{
			if(p->roomId == roomId)
			{
				pold->next = p->next;
				free(p);
				flag = 1;
				break;
			}
			else     //p一开始指向head,head不是要 删除的节点，先将p赋给pold,p指向下一个
			{
				pold = p;
				p = p->next;
			}
		}
	}

	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,we don't have this roomId\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	//printf("headroom=%d\n",head->roomId);
	//printf("next id=%d\n",head->next->roomId);

	fp = fopen(ROOM_FILE,"w");
	if(fp == NULL)
	{
		perror("open roomfile fail\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp, "%-5d", head->roomId);  // -12 zuoduiqi
		fprintf(fp, "%-10s",head->type);
		fprintf(fp, "%-5d",head->price);
		fprintf(fp, "%-5d",head->discount);
		fprintf(fp, "%-5d",head->cashPledge);
		fprintf(fp, "%-5d\n",head->status);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("Delete room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int change_room()
{
	FILE *fp;
	Room *p; //用来遍历链表
	int flag = 0;
	int x,loop = 1;
	int roomId;
	char type[10];
	int price;
	int discount;
	int cashPledge;
	int status;
	Room *head = read_room();

	printf("please input roomId:\n");
	scanf("%d",&roomId);

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back add room\n");
		printf("press any key to continue.\n");
		return 0;
	}

	while(p != NULL)
	{
		if(p->roomId == roomId)
		{
			while(loop)
			{
				printf("which information do you want to change:1.roomId 2.type 3.price 4.discount 5.cashPledge 6.status 0.quit\n");
				scanf("%d",&x);
				switch(x)
				{
					case 1://roomid
						printf("please input new roomId:\n");
						scanf("%d",&roomId);
						p->roomId = roomId;
						break;
					case 2://type
						printf("please input new type:\n");
						scanf("%s",type);
						strcpy(p->type,type);
						break;
					case 3://price
						printf("please input new price:\n");
						scanf("%d",&price);
						p->price = price;
						break;
					case 4://discount
						printf("please input new discount:\n");
						scanf("%d",&discount);
						p->discount = discount;
						break;
					case 5://cash
						printf("please input new cashPledge\n");
						scanf("%d",&cashPledge);
						p->cashPledge = cashPledge;
						break;
					case 6://status
						printf("please input new status\n");
						scanf("%d",&status);
						p->status = status;
						break;
					case 0:
					default:
						loop = 0;
						break;
				}
			}

			flag = 1;
			break;
		}
		else     
			p = p->next;			
	}
	
	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,we don't have this userId\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
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
	printf("change room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int stayroom_status(int roomid) //将入住的房间状态改为 1.不空
{
	FILE *fp;
	Room *p; //用来遍历room链表
	Room *head = read_room();

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back add room\n");
		return 0;
	}

	while(p != NULL)
	{
		if(p->roomId == roomid)
		{
			p->status = 1;//0 empty,1 not empty,2 not clean,3 cleaning
			break;
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

	return 0;
}

int exitroom_status(int roomid)  //将退房的房间状态改成 2.没打扫
{
	FILE *fp;
	Room *p; //用来遍历room链表
	Room *head = read_room();

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back add room\n");
		return 0;
	}

	while(p != NULL)
	{
		if(p->roomId == roomid)
		{
			p->status = 2;//0 empty,1 not empty,2 not clean,3 cleaning
			break;
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

	return 0;
}

