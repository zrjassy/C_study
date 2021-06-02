#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct process_FCFS
{
	char name;			//进程名
	float arrivetime;	//到达时间
	float servetime;	//服务时间
	float finishtime;	//完成时间
	float roundtime;	//周转时间
	float daiquantime;	//带权周转时间
	struct process_FCFS *link;//结构体指针

}FCFS;


void choosemenu()
{
    printf("请选择调度算法：\n");
    printf("a.先来先服务算法\n");
    printf("b.最短进程优先算法\n");
    printf("c.时间片轮转算法\n");
    printf("e.退出程序\n");
}

int main(int argc, char const *argv[])
{
    choosemenu();
    return 0;
}
