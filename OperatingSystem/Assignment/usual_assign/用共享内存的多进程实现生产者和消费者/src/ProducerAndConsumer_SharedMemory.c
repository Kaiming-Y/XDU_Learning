// 题目：用共享内存的多进程实现生产者和消费者

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define BUFFER_SIZE 10

// 定义共享内存的结构
typedef struct {
    int buffer[BUFFER_SIZE];  // 共享缓冲区
    int count;                // 缓冲区中的项目计数器
    int in;                   // 生产者将放置项目的位置
    int out;                  // 消费者将获取项目的位置
} shared_data;

// 定义信号量结构
typedef union {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
} semunion;

// 初始化信号量
int init_semaphore(int semid, int semnum, int value) {
    semunion arg;
    arg.val = value;
    return semctl(semid, semnum, SETVAL, arg);
}

// 等待信号量
int wait_semaphore(int semid, int semnum) {
    struct sembuf operation;
    operation.sem_num = semnum;
    operation.sem_op = -1;  // 等待信号量
    operation.sem_flg = 0;
    return semop(semid, &operation, 1);
}

// 发送信号量
int signal_semaphore(int semid, int semnum) {
    struct sembuf operation;
    operation.sem_num = semnum;
    operation.sem_op = 1;  // 发送信号量
    operation.sem_flg = 0;
    return semop(semid, &operation, 1);
}

// 生产者进程
void producer(int shmid, int semid) {
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0);

    for (int i = 0; i < BUFFER_SIZE * 2; i++) {
        wait_semaphore(semid, 2);  // 等待缓冲区有空位置

        wait_semaphore(semid, 0);  // 加锁互斥信号量

        data->buffer[data->in] = i;  // 将项目放入缓冲区
        data->in = (data->in + 1) % BUFFER_SIZE;  // 更新生产者放置项目的位置
        data->count++;  // 增加缓冲区中的项目计数器

        signal_semaphore(semid, 0);  // 解锁互斥信号量

        signal_semaphore(semid, 1);  // 通知消费者缓冲区已满

        printf("Producer produced item %d\n", i);
        fflush(stdout);

        sleep(1);  // 生产者休眠一秒
    }

    shmdt(data);  // 分离共享内存
}

// 消费者进程
void consumer(int shmid, int semid) {
    shared_data *data = (shared_data *)shmat(shmid, NULL, 0);

    for (int i = 0; i < BUFFER_SIZE * 2; i++) {
        wait_semaphore(semid, 1);  // 等待缓冲区有项目可消费

        wait_semaphore(semid, 0);  // 加锁互斥信号量

        int item = data->buffer[data->out];  // 从缓冲区获取项目
        data->out = (data->out + 1) % BUFFER_SIZE;  // 更新消费者获取项目的位置
        data->count--;  // 减少缓冲区中的项目计数器

        signal_semaphore(semid, 0);  // 解锁互斥信号量

        signal_semaphore(semid, 2);  // 通知生产者缓冲区已空

        printf("Consumer consumed item %d\n", item);
        fflush(stdout);

        sleep(2);  // 消费者休眠两秒
    }

    shmdt(data);  // 分离共享内存
}

int main() {
    key_t key = ftok(".", 'S');  // 创建唯一的key
    int shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666);  // 创建共享内存段

    // 获取共享内存的ID
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    int semid = semget(key, 3, IPC_CREAT | 0666);  // 创建三个信号量

    // 获取信号量的ID
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // 初始化互斥信号量为1，空信号量为BUFFER_SIZE，满信号量为0
    init_semaphore(semid, 0, 1);
    init_semaphore(semid, 1, 0);
    init_semaphore(semid, 2, BUFFER_SIZE);

    pid_t producer_pid = fork();  // 创建生产者进程

    if (producer_pid == -1) {
        perror("fork");
        exit(1);
    } else if (producer_pid == 0) {
        // 子进程执行生产者逻辑
        producer(shmid, semid);
        exit(0);
    }

    pid_t consumer_pid = fork();  // 创建消费者进程

    if (consumer_pid == -1) {
        perror("fork");
        exit(1);
    } else if (consumer_pid == 0) {
        // 子进程执行消费者逻辑
        consumer(shmid, semid);
        exit(0);
    }

    // 等待子进程结束
    waitpid(producer_pid, NULL, 0);
    waitpid(consumer_pid, NULL, 0);

    // 删除共享内存和信号量
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    return 0;
}

