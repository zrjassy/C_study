#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user.h"

#define USER_FILE "user.txt"

int write_user(User *r)
{
	FILE *fp;

	fp = fopen(USER_FILE,"a");
	if(fp == NULL)
	{
		perror("open user file\n");
		return 1;
	}
	fprintf(fp, "%-12s", r->userId);  // -12 zuoduiqi
	fprintf(fp, "%-7s",r->password);
	fprintf(fp, "%-9s",r->name);
	fprintf(fp, "%-4s",r->sex);
	fprintf(fp, "%-8s",r->role);
	fprintf(fp, "%-20s\n",r->email);  // zhuyi jia \n
	fclose(fp);
	return 0;
}


User* read_user()
{
	User *head;
	User *p,*pold,*newNode;
	FILE *fp;
	fp = fopen(USER_FILE,"r");
	if(fp == NULL)
	{
		perror("open user file fail");
		return NULL;
	}
	head = (User *)malloc(sizeof(User));
	memset(head,0,sizeof(User));  // malloc shenqingde kongjian qingling
	head->next = NULL;
	p = head;
	pold = head;
	while(!feof(fp))  
	{
		fscanf(fp,"%s",p->userId);
		fscanf(fp,"%s",p->password);
		fscanf(fp,"%s",p->name);
		fscanf(fp,"%s",p->sex);
		fscanf(fp,"%s",p->role);
		fscanf(fp,"%s",p->email);
		newNode = (User*)malloc(sizeof(User));  //已经到最后一个了，但是还是 会创建出一个，导致多了一个，display的时候就会多出一行
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

int display_user()
{
	User *p;
	int num =  1;
	p = read_user();
	printf("##########################\n");
	while(p->next != NULL)
	{
		printf("%d,ID:%s,Password:%s,Name:%s,Sex:%s,Role:%s,Email:%s\n",
			num,p->userId,p->password,p->name,p->sex,p->role,p->email);
		p = p->next;
		num++;
	}
	getchar();
	printf("##########################\n");
	printf("show user success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


int add_user()    //tianjia zhihou hui xieru wenjian
{
	User *pr;
	char *role_str[]={"admin","manager","recept","cleaner"};
	pr = (User *)malloc(sizeof(User));
	if(pr == NULL)
	{
		printf("malloc error\n");	
		return 1;
	}
	memset(pr,0,sizeof(User));
	getchar();
	printf("please input user id:\n");
	fgets(pr->userId,12,stdin);
	//getchar();
	printf("please input user password:\n");
	fgets(pr->password,7,stdin);
	getchar();

	printf("please select user role:1.admin,2.manager,3.recept,4.cleaner:\n");
	int s;
	scanf("%d",&s);
	while(s<1||s>4)
	{
		printf("select error,again:\n");
		scanf("%d",&s);
	}
	strcpy(pr->role,role_str[s-1]);
	getchar();   
	printf("please input user name:\n");
	fgets(pr->name,8,stdin);
	//getchar();
	printf("please input user's email:\n");
	fgets(pr->email,19,stdin);
	//getchar();
	printf("please input sex(m/f):\n");
	fgets(pr->sex,4,stdin);
	//getchar();
	pr->next = NULL;
	write_user(pr);
	free(pr);

	//getchar();
	printf("Add user success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int deleteuser()   //shanchu yonghu
{
	FILE *fp;
	User *p; //用来遍历用户链表
	int flag = 0;
	char userId[12];
	User *pold;
	User *head = read_user();
	pold = head;

	printf("which user do you want to delete,please input the userId:\n");
	scanf("%s",userId);

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back setup users\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}
	if(strcmp(head->userId,userId) == 0)  //删除首元节点
	{
		head = head->next;
		free(p);
		flag = 1;
	}
	else
	{
		while(p != NULL)
		{
			if(strcmp(p->userId,userId) == 0)
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
		printf("sorry,we don't have this userId\n");
		printf("press any key to continue.\n");
		getchar();
		return 0;
	}


	fp = fopen(USER_FILE,"w");
	if(fp == NULL)
	{
		perror("open roomfile fail\n");
		return 1;
	}
	while(head->next != NULL)
	{
		fprintf(fp, "%-12s", head->userId);  // -12 zuoduiqi
		fprintf(fp, "%-7s",head->password);
		fprintf(fp, "%-9s",head->name);
		fprintf(fp, "%-4s",head->sex);
		fprintf(fp, "%-8s",head->role);
		fprintf(fp, "%-20s\n",head->email);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("Delete user success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}


int initpassword()
{
	FILE *fp;
	User *p; //用来遍历用户链表
	int flag = 0;
	char userId[12];
	User *head = read_user();

	printf("which user's password do you want to reset,please input the userId:\n");
	scanf("%s",userId);

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back setup users\n");
		return 0;
	}

	while(p != NULL)
	{
		if(strcmp(p->userId,userId) == 0)
		{
			strcpy(p->password,"123456");
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

	fp = fopen(USER_FILE,"w");
	if(fp == NULL)
	{
		perror("open user file\n");
		return 1;
	}
	while(head != NULL)
	{
		fprintf(fp, "%-12s", head->userId);  // -12 zuoduiqi
		fprintf(fp, "%-7s",head->password);
		fprintf(fp, "%-9s",head->name);
		fprintf(fp, "%-4s",head->sex);
		fprintf(fp, "%-8s",head->role);
		fprintf(fp, "%-20s\n",head->email);  // zhuyi jia \n

		head = head->next;  //注意加循环!!!
	}
	fclose(fp);

	getchar();
	//printf("flag=%d\n",flag);
	printf("Reset password success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}

int edit_information()
{
	FILE *fp;
	User *p; //用来遍历用户链表
	int flag = 0;
	int x,loop = 1;
	char userId[12];
	char password[7];
	char name[9];
	char email[20];
	User *head = read_user();

	printf("please input your userId:\n");
	scanf("%s",userId);

	p = head;
	
	if(head == NULL)
	{
		printf("System is Empty now,please go back setup users\n");
		return 0;
	}

	while(p != NULL)
	{
		if(strcmp(p->userId,userId) == 0)
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

			flag = 1;
			break;
		}
		else     
			p = p->next;			
	}
	
	if(flag == 0)  //循环完flag还是0则表示没有找到相应的id
	{
		printf("sorry,we don't have this userId\n");
		return 0;
	}

	fp = fopen(USER_FILE,"w");
	if(fp == NULL)
	{
		perror("open file fail\n");
		return 1;
	}
	while(head != NULL)
	{
		fprintf(fp, "%-12s", head->userId);  // -12 zuoduiqi
		fprintf(fp, "%-7s",head->password);
		fprintf(fp, "%-9s",head->name);
		fprintf(fp, "%-4s",head->sex);
		fprintf(fp, "%-8s",head->role);
		fprintf(fp, "%-20s\n",head->email);  // zhuyi jia \n
		head = head->next;
	}
	fclose(fp);

	getchar();
	printf("Edit information success\n");
	printf("press any key to continue.\n");
	getchar();
	return 0;
}