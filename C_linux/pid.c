#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("err\n");
        return 0;
    }
    else if (pid == 0)
    {
        printf("child:%d-%d\n", getpid(), getppid());
        exit(0);
    }
    else
    {
        while (1)
        {
            int status;
            wait(&status);
            sleep(2);
            printf("father:%d-%d\n", getpid(), getppid());
        }
        return 0;
    }
}
