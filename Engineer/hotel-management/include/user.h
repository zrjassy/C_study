#ifndef _USER_H
#define _USER_H

typedef enum {admin,manager,recept,cleaner}ROLE;

struct usernode
{
  char userId[12];
  char name[9];
  char sex[4];
  char role[8];  //"admin"."manager","recept(前台)"."cleaner"
  char email[20];
  char password[7];
  struct usernode *next;
};
typedef struct usernode User;

/**
  *read out all user information
  *from user.txt to user list.
  *
  *return:
  *      success:return list head
  *      failuer:NULL
  */
User *read_user();
/**
 * save one node user information to user.txt
 *
 * parameter:
 *      	User* r:user information struct pointer
 * return:
 *     		success:0
 *       	failure:1
 */
int write_user(User *r);
/**
 * save all user information to user.txt
 * parameter:
 *     		 User *head,user link head pointer
 * return:
 *    		success:0
 *     		failure:1
 */ 

int backup_user();
/**
 * free all user information struct
 */
int backup_room();

int backup_bill();

int backup_cus();

void adminSystem(User *r);

void managerSystem(User *r);

void receptSystem(User *r);

void cleanerSystem(User *r);

void customerSystem();

int display_user();

int add_user();

int deleteuser();

int initpassword();

int edit_information();


#endif