#ifndef _RECEPT_H
#define _RECEPT_H
 
#include "user.h"

struct  customernode
{
	int roomId;
	char cusid[19];  //shen fen zheng
	char cusname[9];
	int cusage;
	char cussex[4];
	char phone[12];
	char inDay[12];
	char outDay[12];
	int status;    //1 .入住  0.以退房
	struct customernode *next;
};

typedef struct customernode Customer;

int receptMenu();  //前台菜单

int write_cus(Customer *r);  //将顾客信息写入文件

int check_stayroom();  //查询房间以及入住

Customer *read_customer();  //读取顾客文件，返回链头

int display_cusinformation();//展示入住客人的信息

int exit_room();  //退房：将房间状态改成 2未打扫，顾客状态改成已退房

int replace_room();  //换房：将原先住的房间状态改成 2未打扫，现住房间状态改成 1不空

int keep_stay();   //续住：将顾客的退房时间改变

int personalinformation(User *r); //更改个人信息

void receptSystem(User *r);

#endif