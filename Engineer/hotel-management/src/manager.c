#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "user.h"
#include "room.h"
#include "bill.h"

int managerMenu()
{
	int c;
	printf("\t\t\t      Hotel Management\n");
	printf("\t\t\t==================================\n");
	printf("\t\t\t      Manager System\n");
	printf("\t\t\t      * 1 show user\n");
	printf("\t\t\t      * 2 add user\n");
	printf("\t\t\t      * 3 remove user\n");
	printf("\t\t\t      * 4 display room\n");
	printf("\t\t\t      * 5 change room\n");
	printf("\t\t\t      * 6 add room\n");
	printf("\t\t\t      * 7 delete room\n");
	printf("\t\t\t      * 8 check bill\n");
	printf("\t\t\t      * 0 quit\n");
	printf("\t\t\t==================================\n");
	printf("please select:\n");
	scanf("%d",&c);
	while(c<0||c>8)
	{
		printf("select error,again:");
		scanf("%d",&c);
	}

	return c;
}


void managerSystem(User *r)
{
	int c,loop=1;
	User *pr;
	//Room *p;
	while(loop)
	{
		system("clear");
		printf("\n%s",r->name);  //左上角输出admin的名字
		//showTime(1);
		c = managerMenu();
		switch(c)
		{
			case 1:
				printf("show user\n");
				pr = read_user();
				display_user(pr);
				break;
			case 2:
				printf("add user\n");
				add_user();
				break;
			case 3:
				printf("delete user\n");  //shanchu yonghu
				pr = read_user();
				deleteuser(pr);
				break;
			case 4:
				printf("display room\n");
				//p = read_room();
				display_room();
				break;
			case 5:
				printf("change room\n");
				change_room();
				break;
			case 6:
				printf("add room\n");
				add_room();
				break;
			case 7:
				printf("delete room\n");
				deleteroom();
				break;
			case 8:
				printf("check bill\n");
				display_bill();
				break;
			case 0:
			default:
				loop = 0;
				break;
		}
	}
}