// 题目：用多线程实现生产者和消费者

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];      // 共享缓冲区
int count = 0;                // 缓冲区中的项目计数器
int in = 0;                   // 生产者将放置项目的位置
int out = 0;                  // 消费者将获取项目的位置

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;    // 互斥锁
pthread_cond_t full = PTHREAD_COND_INITIALIZER;       // 缓冲区满的条件变量
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;      // 缓冲区空的条件变量

void *producer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE * 2; i++) {
        pthread_mutex_lock(&mutex);    // 加锁互斥锁

        // 如果缓冲区已满，等待直到缓冲区有空位置
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = i;                // 将项目放入缓冲区
        in = (in + 1) % BUFFER_SIZE;   // 更新生产者放置项目的位置
        count++;                       // 增加缓冲区中的项目计数器

        pthread_cond_signal(&full);    // 通知消费者缓冲区已满
        pthread_mutex_unlock(&mutex);  // 解锁互斥锁

        printf("Producer produced item %d\n", i);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE * 2; i++) {
        pthread_mutex_lock(&mutex);    // 加锁互斥锁

        // 如果缓冲区为空，等待直到缓冲区有项目
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        int item = buffer[out];         // 从缓冲区获取项目
        out = (out + 1) % BUFFER_SIZE;  // 更新消费者获取项目的位置
        count--;                        // 减少缓冲区中的项目计数器

        pthread_cond_signal(&empty);    // 通知生产者缓冲区已空
        pthread_mutex_unlock(&mutex);   // 解锁互斥锁

        printf("Consumer consumed item %d\n", item);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 创建生产者线程和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 等待线程完成
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}