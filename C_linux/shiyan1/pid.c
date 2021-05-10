#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// 调试子进程时，在luanch.json修改设置
int main(void)
{
    pid_t pid;
    int num = 0;
    int n;
    pid = fork();
    if (pid < 0)
    {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0)
    {
        num += 10;
        printf("child %d\n", num);
        printf("child %p\n", &num);
        printf("PID %d\n",pid);
        printf("This is the child process. My PID is: %d. My PPID is: %d.\n", getpid(), getppid());
        if (execl("/home/jassy/project/c/C_study/C_linux/hello", "hello", NULL) == -1)
        {
            perror("execl error ");
            exit(1);
        }
    }
    else
    {
        sleep(5);
        int status;
        wait(&status);
        num += 20;
        printf("parent %d\n", num);
        printf("parent %p\n", &num);
        printf("child exit，status:%d\n", status);
        printf("This is the parent process. My PID is %d.My Child PID is %d.\n", getpid(), pid);
    }
    return 0;
}
