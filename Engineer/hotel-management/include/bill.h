#ifndef _BILL_H
#define _BILL_H


#include "room.h"
#include "recept.h"

struct billnode
{
  int roomId;
  int price;
  int yingPrice;
  int realPrice;  
  int cashPledge;
  int change;
  int status;  //1.入住押金 0.已还押金
  char inDay[12];
  char outDay[12];
  struct billnode *next;
};

typedef struct billnode Bill;


int write_bill(Bill *r);

int add_bill(Room *p,Customer *pr);

Bill* read_bill();

int display_bill();

int exitroom_billstatus(int roomid,char *inDay,char *outDay);


#endif