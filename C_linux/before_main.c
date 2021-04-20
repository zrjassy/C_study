#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

static void __attribute__((constructor)) before_main(void)
{
    printf("Before main...\n");
}
int main(void)
{
    printf("Main!\n");
    return 0;
}
