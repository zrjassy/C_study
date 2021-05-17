#ifndef _CUSTOMER_H
#define _CUSTOMER_H

typedef struct customer
{
    int roomID;
    char name[10];
    char IDchard[18];  
    char phone[12];   
    char Inday[12];
    struct customer *next;
} Customer;

#define CUSTOMER_FILE "customer.txt"

int add_customer();
int exit_customer();

#endif