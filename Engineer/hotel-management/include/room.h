#ifndef _ROOM_H
#define _ROOM_H
 
typedef enum {EMPTY,NOT_EMPTY,WANT_CLEAR,CLEARING} ROOM_STATUS;

struct  roomnode
{
	int roomId;
	char type[10];
	int price;
	int discount;//0 normal,1 sale
	int cashPledge;
	int status;//0 empty,1 not empty,2 not clean,3 cleaning
	struct roomnode *next;
};

typedef struct roomnode Room;
/**
 * restore all room information from room.txt to list
 * return:
 *      	success: room list head pointer
 * 			failure: NULL
 */

Room *read_room();   //ok

int display_room();  //ok   meiwenti

int add_room(); //ok

int write_room(Room *r);  //ok

int change_room();  //ok

int deleteroom(); //ok

int stayroom_status(int roomid); //将入住的房间状态改为 1.不空

int exitroom_status(int roomid);

#endif