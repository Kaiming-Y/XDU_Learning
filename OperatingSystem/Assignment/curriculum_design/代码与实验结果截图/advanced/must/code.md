# 高级题

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define BUFSZ 8
#define LOCK_BUSY 0
#define LOCK_FREE 1

volatile int* lock;

void lock_acquire(volatile int *lock){
    int tmp = LOCK_BUSY;
    //给tmp设置为LOCK_BUSY，是为了交换时给lock上锁
    //下面汇编的含义就是交换lock和tmp的值，取出lock的值在tmp中
    asm volatile("xchg %0, %1"
                 : "=r"(tmp)   //输出部分
                 : "m"(*lock), "0"(tmp)    //输入部分
                 : "memory");
    //检查tmp是否为上锁状态本质就是看lock
    while (tmp == LOCK_BUSY) {
        asm volatile("pause":::"memory");
        tmp = *lock;
        asm volatile("xchg %0, %1"
                     : "=r"(tmp)
                     : "m"(*lock), "0"(tmp)
                     : "memory");
        //这里不断重复获取lock的值，直到锁被释放tmp就变为LOCK_FREE了。
    }
}

void lock_release(volatile int *lock){
    asm volatile("movl %1, %0"
                 : "+m"(*lock) : "r"(LOCK_FREE)
                 : "memory");
    //释放锁，给lock赋值LOCK_FREE
}

void write_proc(char* fname, char* msg){
    lock_acquire(lock);//请求锁
    int fd = open(fname, O_CREAT|O_WRONLY|O_APPEND, 0666);
    if(fd < 0){
        perror("open failed");
        exit(1);
    }
    // write(fd, msg, strlen(msg));
    for (int i = 0; i < strlen(msg); i++) {
        write(fd, msg+i, 1);
    }
    close(fd);
    lock_release(lock);//释放锁
}

int main(void){
	int shmid;
	key_t key;

	key = ftok("./", 2015);
	if (key == -1) {
		perror("ftok");
	}

	shmid = shmget(key, BUFSZ, IPC_CREAT | 0666);
	if (shmid < 0) {
		perror("shmget");
		exit(-1);
	}
    lock = shmat(shmid, NULL, 0); // 连接共享内存
    *lock = LOCK_FREE;
    int pid = fork();
    char fname[] = "./test.txt";
    char msg1[128], msg2[128];
    sprintf(msg1, "768PROC1 MYFILE1\n");
    sprintf(msg2, "768PROC2 MYFILE2\n");
    if((pid) < 0){
        perror("fork failed");
        exit(1);
    }
    else if(pid == 0){
        //子进程写文件1
        write_proc(fname, msg1);
    }
    else{
        //父进程写文件2
        write_proc(fname, msg2);
    }

    return 0;
}
```

