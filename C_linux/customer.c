# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/types.h>
# include <pthread.h>
# include <semaphore.h>
# include <string.h>
# include <unistd.h>

#define BUFFER_SIZE 5
typedef int buffer_item;

//semaphores
sem_t empty, full, mutex;

//buffer
buffer_item buffer[BUFFER_SIZE];

int in, out;

//存储数据的结构体
struct data {
    int id;
    int opTime;
    int lastTime;
    int productId;
};

//有限缓存插入--生产
int insert_item(buffer_item item) {
    /* insert item into buffer */
    buffer[out] = item;
    out = (out + 1) % BUFFER_SIZE;
    return 0;
}

//有限缓存删除--消费
int remove_item(buffer_item *item) {
    /* remove an object from buffer and then place it in item */
    *item = buffer[in];
    in = (in + 1) % BUFFER_SIZE;
    return 0;   
}

//生产者
void *producer(void* param) {
    int productId = ((struct data*)param)->productId;
    int lastTime = ((struct data*)param)->lastTime;
    int opTime = ((struct data*)param)->opTime;
    int id = ((struct data*)param)->id;

    free(param);

    sleep(opTime);
    sem_wait(&empty);
    sem_wait(&mutex);

    /* critical section */
    //add a item
    insert_item(productId);
    sleep(lastTime);
    printf("Thread %d: Producer produce %d\n", id, productId);

    sem_post(&mutex);
    sem_post(&full);
    pthread_exit(0);
}

//消费者
void *consumer(void* param) {
    int lastTime = ((struct data*)param)->lastTime;
    int opTime = ((struct data*)param)->opTime;
    int id = ((struct data*)param)->id;

    free(param);

    sleep(opTime);
    sem_wait(&full);
    sem_wait(&mutex);

    /* critical section */
    //remove a item
    buffer_item item;
    remove_item(&item);
    sleep(lastTime);
    printf("Thread %d: Consumer consume %d\n", id, item);

    sem_post(&mutex);
    sem_post(&empty);
    pthread_exit(0);
}

int main() {
    //pthread
    pthread_t tid; // the thread identifier

    pthread_attr_t attr; //set of thread attributes

    /* get the default attributes */
    pthread_attr_init(&attr);

    //initial the semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    in = out = 0;

    int id = 0;
    while(scanf("%d", &id) != EOF) {
        char role;      //producer or consumer
        int opTime;     //operating time
        int lastTime;   //run time
        int productId;  //product id
        scanf("%c%d%d", &role, &opTime, &lastTime);
        struct data* d = (struct data*)malloc(sizeof(struct data));
        d->id = id;
        d->opTime = opTime;
        d->lastTime = lastTime;
        if(role == 'P') {
            scanf("%d", &productId);
            d->productId = productId;
            pthread_create(&tid, &attr, producer, d);

        }
        else if(role == 'C')
            pthread_create(&tid, &attr, consumer, d);
    }

    //释放信号量
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}
