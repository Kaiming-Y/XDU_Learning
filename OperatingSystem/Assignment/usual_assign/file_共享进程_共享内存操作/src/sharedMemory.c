#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_SIZE 4096  // 共享内存的大小

int main() {
    int fd;  // 文件描述符
    int shmid;  // 共享内存标识符
    char *shmaddr;  // 指向共享内存的指针
    struct stat file_stat;  // 用于获取文件大小的结构体
    off_t file_size;  // 文件大小

    // 打开文件
    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 获取文件大小
    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        return 1;
    }
    file_size = file_stat.st_size;

    // 创建共享内存
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        close(fd);
        return 1;
    }

    // 连接到共享内存
    shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        close(fd);
        shmctl(shmid, IPC_RMID, NULL);  // 删除共享内存
        return 1;
    }

    // 将文件内容映射到共享内存
    if (file_size > SHM_SIZE) {
        printf("File size exceeds the size of shared memory.\n");
        close(fd);
        shmdt(shmaddr);  // 分离共享内存
        shmctl(shmid, IPC_RMID, NULL);  // 删除共享内存
        return 1;
    }

    if (read(fd, shmaddr, file_size) == -1) {
        perror("read");
        close(fd);
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    // 关闭文件
    close(fd);

    // 在共享内存中操作数据
    printf("Content in shared memory:\n%s\n", shmaddr);

    // 分离共享内存
    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    // 删除共享内存
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        return 1;
    }

    return 0;
}
