#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>
int g_int = 1;
int main()
{
    int local_int = 1;
    int *malloc_int = (int *)malloc(sizeof(int));
    *malloc_int = 1;
    pid_t pid = fork();
    if (pid == 0) /*子进程 */
    {
        local_int = 0;
        g_int = 0;
        *malloc_int = 0;
        fprintf(stderr, "[CHILD ] child change local global malloc value to 0\n");
        free(malloc_int);
        sleep(10);
        fprintf(stderr, "[CHILD ] child exit\n");
        exit(0);
    }
    else if (pid < 0)
    {
        printf("fork failed (%s)", strerror(errno));
        return 1;
    }
    fprintf(stderr, "[PARENT] wait child exit\n");
    waitpid(pid, NULL, 0);
    fprintf(stderr, "[PARENT] child have exit\n");
    printf("[PARENT] g_int = %d\n", g_int);
    printf("[PARENT] local_int = %d\n", local_int);
    printf("[PARENT] malloc_int = %d\n", local_int);
    free(malloc_int);
    return 0;
}
