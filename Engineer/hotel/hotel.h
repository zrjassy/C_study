#ifndef _HOTEL_H
#define _HOTEL_H

typedef enum {EMPTY,CLEAN,NOTCLEAN} room_status;

typedef struct room
{
    int ID;
    char Type[10];
    int status;  // 0为空
    int price;
};


#endif