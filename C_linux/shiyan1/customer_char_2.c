#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 5
typedef char buffer_item;

//semaphores full表示已有的个数，empty表示空的个数
sem_t empty1, full1, mutex1;
sem_t empty2, full2, mutex2;
sem_t exit1;

// buffer1 存储输入的小写字母
// buffer2 存储转换的大写字母
buffer_item buffer1[BUFFER_SIZE];
buffer_item buffer2[BUFFER_SIZE];

int in1, out1;
int in2, out2;

// 生产者线程 负责将键盘输入的小写字母保存至buffer1中
void *producer(void *args)
{
    char role;
    while (1)
    {
        scanf("%c", &role);
        if(role=='\n')
            continue;
        // printf("\nTest %c\n", role);
        sem_wait(&empty1);
        sem_wait(&mutex1);
        //add a item
        buffer1[in1] = role;
        in1 = (in1 + 1) % BUFFER_SIZE;
        sem_post(&mutex1);
        sem_post(&full1);
        if (role > 'z' || role < 'a')
            break;
        else
            printf("\nThread 1: Producer produce %c\n", role);
    }
    pthread_exit(0);
}

// 消费者线程 负责将buffer1中的小写字母转换成大写字母并保存至buffer2中
void *consumer(void *args)
{
    while (1)
    {
        // sleep(5);
        // 从队列1中取数据
        sem_wait(&full1);
        sem_wait(&mutex1);
        buffer_item item;
        item = buffer1[out1];
        out1 = (out1 + 1) % BUFFER_SIZE;
        sem_post(&mutex1);
        sem_post(&empty1);
        // 大小写转换后将数据存入队列2
        sem_wait(&empty2);
        sem_wait(&mutex2);
        char item2 = item - 32;
        buffer2[in2] = item2;
        in2 = (in2 + 1) % BUFFER_SIZE;
        // sleep(10);
        sem_post(&mutex2);
        sem_post(&full2);

        if (item > 'z' || item < 'a')
            break;
        else
            printf("\nThread 2: Consumer consume %c\n", item);
    }
    pthread_exit(0);
}

void *printchar(void *args)
{
    while (1)
    {
        sleep(1);
        sem_wait(&full2);
        sem_wait(&mutex2);
        buffer_item item;
        item = buffer2[out2];
        if (item + 32 > 'z' || item + 32 < 'a')
            break;
        out2 = (out2 + 1) % BUFFER_SIZE;
        // sleep(5);
        printf("\nThread 3: Print %c\n", item);
        sem_post(&mutex2);
        sem_post(&empty2);
    }
    pthread_exit(0);
}

int main()
{
    //pthread
    pthread_t tid1, tid2, tid3; // the thread identifier
    pthread_attr_t attr;        //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initial the semaphores
    sem_init(&mutex1, 0, 1);
    sem_init(&empty1, 0, BUFFER_SIZE);
    sem_init(&full1, 0, 0);
    sem_init(&mutex2, 0, 1);
    sem_init(&empty2, 0, BUFFER_SIZE);
    sem_init(&full2, 0, 0);

    in1 = out1 = 0;
    in2 = out2 = 0;
    pthread_create(&tid1, &attr, producer, NULL);
    pthread_create(&tid2, &attr, consumer, NULL);
    pthread_create(&tid3, &attr, printchar, NULL);

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    //释放信号量
    sem_destroy(&mutex1);
    sem_destroy(&empty1);
    sem_destroy(&full1);
    sem_destroy(&mutex2);
    sem_destroy(&empty2);
    sem_destroy(&full2);

    return 0;
}