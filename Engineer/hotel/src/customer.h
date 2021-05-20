#ifndef _CUSTOMER_H
#define _CUSTOMER_H

typedef struct customer
{
    int roomID;
    char name[10];
    char IDchard[18];  
    char phone[12];   
    int Inday;
    int Outday;
    int deposit;
    int status; // 1为入住，0为退房
    struct customer *next;
} Customer;

int write_customer(Customer *c);
Customer *read_customer();
int free_customer(Customer *head);
int add_customer();
int exit_customer();

#endif