#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "room.h"
#include "recept.h"
#include "bill.h"

#define CUSTOMER_FILE "customer.txt"
#define USER_FILE "user.txt"

int receptMenu()
{
	int c;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t=========================================\n");
	printf("\t\t\t      Recept System\n");
	printf("\t\t\t      * 1 check and stay room\n");
	printf("\t\t\t      * 2 exit room\n");
	printf("\t\t\t      * 3 change room\n");
	printf("\t\t\t      * 4 keep stay\n");
	printf("\t\t\t      * 5 check customer information\n");
	printf("\t\t\t      * 6 edit personal information\n");
	printf("\t\t\t      * 0 quit\n");
	printf("\t\t\t=========================================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>6)
	{
		printf("select error,again:\n");
		scanf("%d",&c);
	}

	return c;
}

int write_cus(Customer *r)   //jia diyige
{
	FILE *fp;

	fp = fopen(CUSTOMER_FILE,"a");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	fprintf(fp,"%-5d",r->roomId);  
	fprintf(fp,"%-19s",r->cusid);
	fprintf(fp,"%-9s",r->cusname);
	fprintf(fp,"%-5d",r->cusage);
	fprintf(fp,"%-4s",r->cussex);
	fprintf(fp,"%-12s",r->phone);
	fprintf(fp,"%-12s",r->inDay);
	fprintf(fp,"%-12s",r->outDay);
	fprintf(fp,"%-5d\n",r->status);  // zhuyi jia \n
	fclose(fp);
	return 0;
}

int check_stayroom()  //查询房间以及入住
{
	int num = 1;
	int roomid;
	Room *p;
	Customer *pr;

	p = read_room();

	printf("##########################\n");   //先显示现在客房的信息
	printf("Room information:\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
			num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);
		p = p->next;
		num++;
	}
	printf("##########################\n");
	printf("which room do you want to choose,please input roomid:\n");
	scanf("%d",&roomid);
	
	p = read_room();
	while(p != NULL)
	{
		if(p->roomId == roomid)
		{
			if((p->status == 1) || (p->status == 2) || (p->status == 3))
			{
				getchar();
				printf("the room is not available\n");
				printf("press any key to continue.\n");
				getchar();
				return 0;
			}
			break;    //此时p指向要入住的房间
		}
		p = p->next;
	}
	printf("choose success,please input customer information:\n");

	stayroom_status(roomid);//还需要把入驻的房间状态选为不空

	pr = (Customer *)malloc(sizeof(Customer));
	if(pr == NULL)
	{
		printf("malloc error\n");	
		return 1;
	}
	memset(pr,0,sizeof(Customer));
	getchar();

	pr->roomId = roomid;
	printf("please input customer ID\n"); //shenfenzheng
	fgets(pr->cusid,18,stdin);
	//getchar();
	printf("please input customer name\n");
	fgets(pr->cusname,8,stdin);
	//getchar();
	printf("please input customer age\n");
	scanf("%d",&pr->cusage);
	getchar();
	printf("please input customer sex\n");
	fgets(pr->cussex,3,stdin);
	//getchar();
	printf("please input customer phone number\n");
	fgets(pr->phone,11,stdin);
	//getchar();
	printf("please input inDay\n");
	fgets(pr->inDay,11,stdin);
	//getchar();
	printf("please input outDay\n");
	fgets(pr->outDay,11,stdin);
	//getchar();
	printf("please input customer status:1.入住 0.已退房\n");
	scanf("%d",&pr->status);
	pr->next = NULL;

	add_bill(p,pr);  //添加账单  
	write_cus(pr);   //将顾客信息写入文件
	free(pr);

	getchar();
	printf("stay room success\n");
	printf("press any key to continue\n");
	getchar();
	return 0;

}

Customer *read_customer()
{
	Customer *head;
	Customer *p,*pold,*newNode;
	FILE *fp;
	fp = fopen(CUSTOMER_FILE,"r");
	if(fp == NULL)
	{
		perror("open file fail");
		return NULL;
	}
	head = (Customer *)malloc(sizeof(Customer));
	memset(head,0,sizeof(Customer));  // malloc shenqingde kongjian qingling
	head->next = NULL;
	p = head;
	//pold = head;
	while(!feof(fp))  
	{
		fscanf(fp,"%d",&p->roomId);  
		fscanf(fp,"%s",p->cusid);
		fscanf(fp,"%s",p->cusname);
		fscanf(fp,"%d",&p->cusage);
		fscanf(fp,"%s",p->cussex);
		fscanf(fp,"%s",p->phone);
		fscanf(fp,"%s",p->inDay);
		fscanf(fp,"%s",p->outDay);
		fscanf(fp,"%d",&p->status);
		newNode = (Customer *)malloc(sizeof(Customer));  //已经到最后一个了，但是还是 会创建出一个，导致多了一个，display的时候就会多出一行
		memset(newNode,0,sizeof(Customer));
		pold = p;    //pold yonglai zhixiang p de qian yige
		p->next = newNode;
		p = newNode;
	}
	pold->next = NULL;  
	free(p);
	fclose(fp);
	return head;
}

int display_cusinformation()
{
	Customer *p;
	int num =  1;
	p = read_customer();
	if(p == NULL)
	{
		getchar();
		printf("there is no customer information...\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	printf("##########################\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,Customer ID:%s,Customer name:%s,Customer age:%d,Customer sex:%s,Customer phone:%s,Customer inDay:%s,Customer outDay:%s,status:%d\n",
			num,p->roomId,p->cusid,p->cusname,p->cusage,p->cussex,p->phone,p->inDay,p->outDay,p->status);
		p = p->next;
		num++;
	}
	getchar();
	printf("##########################\n");
	printf("show customer information success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int exit_room()
{
	Room *p;
	Customer *pr,*head;
	int roomid,num = 1;
	int flag = 0;
	char ID[19];
	char inDay[12],outDay[12];
	p = read_room();
	head = read_customer();
	pr = head;

	printf("##########################\n");   //先显示现在客房的信息
	printf("Room information:\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
			num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);
		p = p->next;
		num++;
	}
	printf("##########################\n");

	printf("please input customer ID:\n");
	scanf("%s",ID);
	//printf("which room do you want to exit,please input the roomid:\n");
	//scanf("%d",&roomid);

	while(pr != NULL)
	{
		if(strcmp(pr->cusid,ID) == 0)
		{
			roomid = pr->roomId;       //拿到退房顾客的房间号，入房时间，退房时间
			strcpy(inDay,pr->inDay);
			strcpy(outDay,pr->outDay);
			pr->status = 0;    //将客人的状态改成 0.已退房
			flag = 1;
			break;
		}
		pr = pr->next;
	}

	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,customer ID error\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}


	FILE *fp;

	fp = fopen(CUSTOMER_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-19s",head->cusid);
		fprintf(fp,"%-9s",head->cusname);
		fprintf(fp,"%-5d",head->cusage);
		fprintf(fp,"%-4s",head->cussex);
		fprintf(fp,"%-12s",head->phone);
		fprintf(fp,"%-12s",head->inDay);
		fprintf(fp,"%-12s",head->outDay);
		fprintf(fp,"%-5d\n",head->status);
		head = head->next;
	}
	fclose(fp);

	exitroom_status(roomid);   //将退房的房间状态改成 2.没打扫
	exitroom_billstatus(roomid,inDay,outDay);

	getchar();
	printf("exit room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


int replace_room()
{
	Room *p;
	Customer *pr;
	char ID[19];
	int roomid,roomid1,flag = 0;
	int x = 0,num = 1;
	pr = read_customer();
 	p = read_room();

	printf("##########################\n");   //先显示现在客房的信息
	printf("Room information:\n");
	while(p->next != NULL)
	{
		printf("%d,roomId:%d,Type:%s,price:%d,discount:%d,cashPledge:%d,status:%d\n",
			num,p->roomId,p->type,p->price,p->discount,p->cashPledge,p->status);
		p = p->next;
		num++;
	}
	printf("##########################\n");

	p = read_room();
	while(p != NULL)    //先判断有没有空的房间
	{
		if(p->status == 0)
		{
			x = 1;
			break;
		}
		p = p->next;
	}
	if(x == 0)
	{
		printf("there is no room available\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}

	printf("please input customer ID:\n");
	scanf("%s",ID);
	while(pr != NULL)
	{
		if(strcmp(pr->cusid,ID) == 0)    //如果身份证号吻合，将原先的房间号拿出来，状态改成 2.没打扫
		{
			roomid = pr->roomId;
			flag = 1;
			break;
		}
		pr = pr->next;
	}
	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,we don't have this userId\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}


	exitroom_status(roomid);   //将原先的房间号拿出来，状态改成 2.没打扫

	printf("which room do you want to change,please input roomid:\n");
	scanf("%d",&roomid1);

	stayroom_status(roomid1);  //将入住的房间状态改为 1.不空

	getchar();
	printf("change room success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int keep_stay()   //续住：将顾客的退房时间改变
{
	Customer *pr,*head;
	char  ID[19];
	char outday[12];
	int flag = 0;
	head = read_customer();
	pr = head;

	printf("please input customer ID:\n");
	scanf("%s",ID);
	while(pr != NULL)
	{
		if(strcmp(pr->cusid,ID) == 0)    
		{
			printf("please input outday:\n");
			scanf("%s",outday);
			strcpy(pr->outDay,outday);
			flag = 1;
			break;
		}
		pr = pr->next;
	}
	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,we don't have this userId\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}

	FILE *fp;

	fp = fopen(CUSTOMER_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-19s",head->cusid);
		fprintf(fp,"%-9s",head->cusname);
		fprintf(fp,"%-5d",head->cusage);
		fprintf(fp,"%-4s",head->cussex);
		fprintf(fp,"%-12s",head->phone);
		fprintf(fp,"%-12s",head->inDay);
		fprintf(fp,"%-12s",head->outDay);
		fprintf(fp,"%-5d\n",head->status);
		head = head->next;
	}
	fclose(fp);


	getchar();
	printf("keep stay success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int personalinformation(User *r)
{
	FILE *fp;
	User *p; //用来遍历用户链表
	int x,loop = 1;
	char userId[12];
	char password[7];
	char name[9];
	char email[20];
	User *head = read_user();
	p = head;
	
	while(p != NULL)
	{
		if(strcmp(p->userId,r->userId) == 0)
		{
			while(loop)
			{
				printf("which information do you want to change:1.userId 2.password 3.name 4.email 0.quit\n");
				scanf("%d",&x);
				switch(x)
				{
					case 1://userid
						printf("please input your new userId:\n");
						scanf("%s",userId);
						strcpy(p->userId,userId);
						break;
					case 2://password
						printf("please input new password:\n");
						scanf("%s",password);
						strcpy(p->password,password);
						break;
					case 3://name
						printf("please input new name:\n");
						scanf("%s",name);
						strcpy(p->name,name);
						break;
					case 4://email
						printf("please input new email:\n");
						scanf("%s",email);
						strcpy(p->email,email);
						break;
					case 0:
					default:
						loop = 0;
						break;
				}
			}
			break;
		}
		else     
			p = p->next;			
	}
	

	fp = fopen(USER_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	while(head != NULL)
	{
		fprintf(fp, "%-12s",head->userId);  // -12 zuoduiqi
		fprintf(fp, "%-7s",head->password);
		fprintf(fp, "%-9s",head->name);
		fprintf(fp, "%-4s",head->sex);
		fprintf(fp, "%-8s",head->role);
		fprintf(fp, "%-20s\n",head->email);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("Edit personal information success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


void receptSystem(User *r)
{
	int c,loop=1;
	//User *pr;
	//Room *p;
	while(loop)
	{
		system("clear");
		printf("\n%s",r->name);  //左上角输出recept的名字
		//showTime(1);
		c = receptMenu();
		switch(c)
		{
			case 1:
				printf("check and stay room\n");
				check_stayroom();
				break;
			case 2:
				printf("exit room\n");
				exit_room();
				break;
			case 3:
				printf("change room\n"); 
				replace_room();
				break;
			case 4:
				printf("keep stay\n");
				keep_stay();
				break;
			case 5:
				printf("check customer information\n");
				display_cusinformation();
				break;
			case 6:
				printf("edit personal information\n");
				personalinformation(r);
				break;
			case 0:
			default:
				loop = 0;
				break;
		}
	}
}