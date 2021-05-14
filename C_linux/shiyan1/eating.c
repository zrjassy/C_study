#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define True 1
#define Flase 0
// semaphares
sem_t se,sa,sb;

void *father(void *args)
{   
    while (True)
    {
        sem_wait(&se);
        sleep(5);
        printf("father puts an apple.\n");
        sem_post(&sa);
    }
}

void *mather(void *args)
{   
    while (True)
    {
        sem_wait(&se);
        sleep(5);
        printf("mather puts a banana.\n");
        sem_post(&sb);
    }
}

void *son(void *args)
{   
    while (True)
    {
        sem_wait(&sa);
        sleep(6);
        printf("son eats an apple.\n");
        sem_post(&se);
    }
}

void *daughter(void *args)
{   
    while (True)
    {
        sem_wait(&sb);
        sleep(6);
        printf("daughter eats a banana.\n");
        sem_post(&se);
    }
}

int main(int argc, char const *argv[])
{
    //pthread
    pthread_t tid1,tid2,tid3,tid4; // the thread identifier

    pthread_attr_t attr; //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);
    sem_init(&se, 0, 0);
    sem_init(&sa, 0, 1);
    sem_init(&sb, 0, 1);
    pthread_create(&tid1, &attr, father, NULL);
    pthread_create(&tid2, &attr, mather, NULL);
    pthread_create(&tid3, &attr, son, NULL);
    pthread_create(&tid4, &attr, daughter, NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    //释放信号量
    sem_destroy(&se);
    sem_destroy(&sa);
    sem_destroy(&sb);

    return 0;
}

