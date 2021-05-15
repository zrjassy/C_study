#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bill.h"
#include "recept.h"

#define BILL_FILE "bill.txt"

int write_bill(Bill *r)
{
	FILE *fp;

	fp = fopen(BILL_FILE,"a");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	fprintf(fp,"%-5d",r->roomId);  
	fprintf(fp,"%-5d",r->price);
	fprintf(fp,"%-5d",r->yingPrice);
	fprintf(fp,"%-5d",r->realPrice);
	fprintf(fp,"%-5d",r->cashPledge);
	fprintf(fp,"%-5d",r->change);
	fprintf(fp,"%-5d",r->status);  //1.入住押金 0.已还押金
	fprintf(fp,"%-12s",r->inDay);
	fprintf(fp,"%-12s\n",r->outDay);  // zhuyi jia \n
	fclose(fp);
	return 0;
}


int add_bill(Room *p,Customer *pr)
{
	Bill *k;
	k = (Bill *)malloc(sizeof(Bill));
	if(k == NULL)
	{
		perror("malloc fail\n");
		return 1;
	}
	memset(k,0,sizeof(Bill));

	k->roomId = p->roomId;
	k->price = p->price;
	k->yingPrice = p->price * (pr->outDay - pr->inDay + 1);
	if(p->discount == 1)
	{
		k->realPrice = k->yingPrice * 0.9;
	}
	else
	{
		k->realPrice = k->yingPrice;
	}
	k->cashPledge = p->cashPledge;
	k->change = 0;
	k->status = 1;   //1.入住押金 0.已还押金
	strcpy(k->inDay,pr->inDay);
	strcpy(k->outDay,pr->outDay);
	k->next = NULL;

	write_bill(k);
	free(k);

	return 0;
}

Bill* read_bill()
{
	Bill *head;
	Bill *p,*pold,*newNode;
	FILE *fp;
	fp = fopen(BILL_FILE,"r");
	if(fp == NULL)
	{
		perror("open bill file fail");
		return NULL;
	}
	head = (Bill *)malloc(sizeof(Bill));
	memset(head,0,sizeof(Bill));  // malloc shenqingde kongjian qingling
	head->next = NULL;
	p = head;
	pold = head;
	while(!feof(fp))  
	{
		fscanf(fp,"%d",&p->roomId);  
		fscanf(fp,"%d",&p->price);
		fscanf(fp,"%d",&p->yingPrice);
		fscanf(fp,"%d",&p->realPrice);	
		fscanf(fp,"%d",&p->cashPledge);
		fscanf(fp,"%d",&p->change);
		fscanf(fp,"%d",&p->status);  //1.入住押金 0.已还押金
		fscanf(fp,"%s",p->inDay);
		fscanf(fp,"%s",p->outDay);
		newNode = (Bill *)malloc(sizeof(Bill));  //已经到最后一个了，但是还是 会创建出一个，导致多了一个，display的时候就会多出一行
		memset(newNode,0,sizeof(User));
		p->next = newNode;
		pold = p;    //pold yonglai zhixiang p de qian yige
		p = newNode;
	}
	pold->next = NULL;  
	free(p);
	fclose(fp);
	return head;
}

int display_bill()
{
	Bill *p;
	int num =  1;
	p = read_bill();
	printf("##########################\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,price:%d,yingPrice:%d,realPrice:%d,cashPledge:%d,change:%d,status:%d,inDay:%s,outDay:%s\n",
			num,p->roomId,p->price,p->yingPrice,p->realPrice,p->cashPledge,p->change,p->status,p->inDay,p->outDay);
		p = p->next;
		num++;
	}
	getchar();
	printf("##########################\n");
	printf("display bill success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int exitroom_billstatus(int roomid,char *inDay,char *outDay)  //退房后将房间账单的状态改成 0.已还押金
{
	FILE *fp;
	Bill *p; //用来遍历bill链表
	Bill *head = read_bill();

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
			if(strcmp(p->inDay,inDay) == 0)
			{
				if(strcmp(p->outDay,outDay) == 0)
				{
					p->status = 0;
					break;
				}
			}
		}
		else     
			p = p->next;			
	}


	fp = fopen(BILL_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-5d",head->price);
		fprintf(fp,"%-5d",head->yingPrice);
		fprintf(fp,"%-5d",head->realPrice);
		fprintf(fp,"%-5d",head->cashPledge);
		fprintf(fp,"%-5d",head->change);
		fprintf(fp,"%-5d",head->status);  //1.入住押金 0.已还押金
		fprintf(fp,"%-12s",head->inDay);
		fprintf(fp,"%-12s\n",head->outDay);
		head = head->next;
	}
	fclose(fp);

	return 0;
}