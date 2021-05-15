#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "room.h"
#include "bill.h"
#include "recept.h"

int adminMenu()
{
	int c;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t==================================\n");
	printf("\t\t\t      Administrator System\n");
	printf("\t\t\t      * 1 show user\n");
	printf("\t\t\t      * 2 add user\n");
	printf("\t\t\t      * 3 remove user\n");
	printf("\t\t\t      * 4 reset user password\n");
	printf("\t\t\t      * 5 edit user information\n");
	printf("\t\t\t      * 6 backup system\n");
	printf("\t\t\t      * 0 quit\n");
	printf("\t\t\t==================================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>6)
	{
		printf("select error,again:\n");
		scanf("%d",&c);
	}

	return c;
}

int backup_user()
{
	User *head = read_user();
	struct tm *newtime;
	char outfile[128];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile,128,"user_%Y%m%d_%H%M%S.txt",newtime);
	FILE *fp;
	fp = fopen(outfile,"w");
	if(fp == NULL)
	{
		perror("open user file\n");
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

	//getchar();
	printf("backup user success\n");
	return 0;
}

int backup_room()
{
	Room *head = read_room();
	struct tm *newtime;
	char outfile[128];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile,128,"room_%Y%m%d_%H%M%S.txt",newtime);
	FILE *fp;
	fp = fopen(outfile,"w");
	if(fp == NULL)
	{
		perror("open room file\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp,"%-5d",head->roomId);  
		fprintf(fp,"%-10s",head->type);
		fprintf(fp,"%-5d",head->price);
		fprintf(fp,"%-5d",head->discount);
		fprintf(fp,"%-5d",head->cashPledge);
		fprintf(fp,"%-5d\n",head->status);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	//getchar();
	printf("backup room success\n");
	return 0;
}

int backup_bill()
{
	Bill *head = read_bill();
	struct tm *newtime;
	char outfile[128];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile,128,"bill_%Y%m%d_%H%M%S.txt",newtime);
	FILE *fp;
	fp = fopen(outfile,"w");
	if(fp == NULL)
	{
		perror("open bill file\n");
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
		fprintf(fp,"%-12s\n",head->outDay);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	//getchar();
	printf("backup bill success\n");
	return 0;
}


int backup_cus()
{
	Customer *head = read_customer();
	struct tm *newtime;
	char outfile[128];
	time_t t1;
	t1 = time(NULL);
	newtime = localtime(&t1);
	strftime(outfile,128,"cus_%Y%m%d_%H%M%S.txt",newtime);
	FILE *fp;
	fp = fopen(outfile,"w");
	if(fp == NULL)
	{
		perror("open customer file\n");
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
		fprintf(fp,"%-5d\n",head->status);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("backup customer success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


void adminSystem(User *r)
{
	int c,loop=1;
	//User *pr;
	while(loop)
	{
		system("cls");
		printf("\n%s",r->name);  //左上角输出admin的名字
		//showTime(1);
		c = adminMenu();
		switch(c)
		{
			case 1:
				printf("show user\n");
				//pr = read_user();
				display_user();
				//scanf("%d",&c);   //show user hou keyi jixu 23456 de caozuo
				break;
			case 2:
				printf("add user\n");
				add_user();
				//scanf("%d",&c);
				break;
			case 3:
				printf("delete user\n");  //shanchu yonghu
				//pr = read_user();
				deleteuser();
				//scanf("%d",&c);
				break;
			case 4:
				printf("reset user password\n");  //初始化密码为123456
				initpassword();
				//scanf("%d",&c);
				break;
			case 5:
				printf("edit user information\n");
				edit_information();  //r就是登陆时的账号密码，改信息只能改自己的，所以传r进来
				//scanf("%d",&c);
				break;
			case 6:
				printf("wait...\n");
				backup_user();
				backup_room();
				backup_bill();
				backup_cus();
				break;
			case 0:
			default:
				loop = 0;
				break;
		}
	}

}