#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "user.h"

void showTime(int k)
{//显示当前时间
    //system("clear");
    struct tm *ptr;
    time_t it;
    it=time(NULL);
    ptr=localtime(&it);
    if(ptr->tm_hour>=5&&ptr->tm_hour<9)
        printf("早上好！\n");
    else if(ptr->tm_hour>=9&&ptr->tm_hour<12)
        printf("上午好！\n");
    else if(ptr->tm_hour>=12&&ptr->tm_hour<14)
        printf("中午好！\n");
    else if(ptr->tm_hour>=14&&ptr->tm_hour<18)
        printf("下午好！\n");
    else
        printf("晚上好！\n");
    printf("现在是%4d年%02d月%02d日 %d:%d:%d\n",
    	ptr->tm_year+1900,ptr->tm_mon+1,ptr->tm_mday,ptr->tm_hour,ptr->tm_min,ptr->tm_sec);
    switch(k)
    {
        case 1:
            printf("欢迎使用旅馆管理系统！\n");
            break;
        case 0:
            printf("谢谢使用旅馆管理系统！\n");
            break;
    }
}


int mainMenu()
{
	int c;
	int k;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t===============================\n");
	printf("\t\t\t      1 : User Login\n");
	printf("\t\t\t      2 : Customer\n");
	printf("\t\t\t      0 : quit\n");
	printf("\t\t\t===============================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>2)
	{
		printf("input error,again:\n");
		scanf("%d",&c);
	}

	if(c == 1 || c ==2)
		k = 1;
	else if(c == 0)
		k = 0;
	showTime(k);
	return c;
}

User *login_user()
{
	int flag;
	int count = 0;//
	char userId[12];
	char password[7];
	User *pr,*p;

	if(access("user.txt",F_OK) != 0)  //如果文件内没有信息，新创一个管理员的账号
	{
		printf("System is Empty,Enter Admin ID and password!\n");
		printf("============================================\n");
		printf("please input Admin ID:\n");
		scanf("%s",userId);
		count ++;
		while(strcmp(userId,"admin1001") != 0)
		{	
			printf("Admin ID error,you have %d chance,please input again:\n",3 - count++);
			scanf("%s",userId);
			if(count > 3) 
			{
				printf("Sorry!\n");
				return NULL;
			}
		}
		printf("============================================\n");
		printf("please input Admin password:\n");
		count = 0;
		scanf("%s",password);
		count++;
		while(strcmp(password,"123456") != 0)
		{	printf("password error,you have %d chance,please input again:\n",3 - count++);
			scanf("%s",password);
			if(count > 3) 
			{
				printf("Sorry!\n");
				return NULL;
			}
		}

		pr = (User *)malloc(sizeof(User));
		if(pr == NULL)
		{
			return NULL;
		}
		memset(pr,0,sizeof(User));
		strcpy(pr->userId,userId);
		strcpy(pr->password,password);
		strcpy(pr->role,"admin");
		getchar();   
		printf("please input admin name:\n");
		fgets(pr->name,8,stdin);
		//getchar();
		printf("please input admin's email:\n");
		fgets(pr->email,19,stdin);
		//getchar();
		printf("please input sex(m/f):\n");
		fgets(pr->sex,4,stdin);
		//getchar();
		write_user(pr);
		return pr;
	}
	else
	{
		getchar();

		pr = (User *)malloc(sizeof(User)); //存放要读的用户的信息，以供进入系统
		if(pr == NULL)
		{
			return NULL;
		}

		printf("please input your userId:\n");
		flag = 0;
		while(flag == 0)
		{
			scanf("%s",userId);
			count++;
			p = read_user();
			while(p != NULL)
			{
			//scanf("%s",userId);
			//count++;
				if(strcmp(p->userId,userId) == 0)
				{
					strcpy(pr->userId,userId);
					flag = 1;
					break;
				}
				p = p->next;
				flag = 0;
			}
			if(count > 3) 
			{
				printf("Sorry!\n");
				return NULL;
			}
			if(flag == 0)
				printf("userId error,you have %d chance,please input again:\n",3 - count);
		}
		printf("============================================\n");

		printf("please input your password:\n");
		count = 0;flag = 0;

		while(flag == 0)
		{
			scanf("%s",password);
			count++;
			//p = read_user();
			//while(p != NULL)
			//{
			if(strcmp(password,p->password) == 0)
			{
				strcpy(pr->password,password);
				strcpy(pr->role,p->role);
				strcpy(pr->name,p->name);
				strcpy(pr->sex,p->sex);
				strcpy(pr->email,p->email);
				flag = 1;
				//break;
			}
				//p = p->next;
			//}
			//printf("%s\n",p->role);
			//printf("%s\n",p->name);
			if(count > 3) 
			{
				printf("Sorry!\n");
				return NULL;
			}
			if(flag == 0)
				printf("password error,you have %d chance,please input again:\n",3 - count);
		}
		getchar();
		printf("============================================\n");
		printf("login success!\n");
		printf("press any key to continue.\n");
		getchar();
		//display_user(pr);
		return pr;
	}

}

void enterSystem(User *r)
{
	//printf("user role:%s\n",r->role);
	//getchar();
	if(strcmp(r->role,"admin") == 0)
		adminSystem(r);
	if(strcmp(r->role,"manager") == 0)
		managerSystem(r);
	if(strcmp(r->role,"recept") == 0)
		receptSystem(r);
	if(strcmp(r->role,"cleaner") == 0)
		cleanerSystem(r);
	else
		printf("\nrole error\n");
}


int main(int argc, char const *argv[])
{
	User *r;
	int c,loop=1;
	while(loop)
	{
		system("cls");
		c = mainMenu();
		switch(c)
		{
			case 1://user
				r = login_user();
				if(r == NULL)
					loop = 0;
				else
					enterSystem(r);
				break;
			case 2://customer
				customerSystem();
				break;
			default:
				loop = 0;
				break;
		}
	}
	return 0;
}