#ifndef _HOTEL_H
#define _HOTEL_H

typedef enum {EMPTY,CLEAN,NOTCLEAN} room_status;

typedef struct room
{
    int ID;
    char Type[10];
    int status;  // 0为空
    int price;   // 每天的价格
    struct room *next;
} ROOM;

// 向文件中写入一个房间信息，返回1成功，0失败
int write_room(ROOM *r);
// 将文件中的房间信息全部读取，返回头结点。
ROOM *read_room();
// 改变房间信息，比如入住信息等，可以选择在函数内输入改变项，也可以作为函数参数
int change_room();
// 查找并显示房间信息
int find_room();
// 管理员添加房间信息
int add_room();
// 住宿选项
int hotel_menu();
// 住宿系统
void hotel_system();
#endif