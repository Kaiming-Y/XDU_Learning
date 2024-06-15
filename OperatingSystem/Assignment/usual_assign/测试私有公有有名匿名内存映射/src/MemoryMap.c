//题目： 测试有名/匿名，共有/私有内存映射

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 100

int main() {
    int fd_named, fd_anonymous;
    void *shared_memory_named, *shared_memory_anonymous;
    char *message = "Hello, shared memory!";
    int message_size = strlen(message) + 1;

    // 有名共有内存映射
    fd_named = shm_open("/my_shared_memory", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd_named == -1) {
        perror("shm_open (named)");
        exit(1);
    }

    if (ftruncate(fd_named, BUFFER_SIZE) == -1) {
        perror("ftruncate (named)");
        exit(1);
    }

    // 有名共享内存映射，共有
    shared_memory_named = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd_named, 0);
    if (shared_memory_named == MAP_FAILED) {
        perror("mmap (named)");
        exit(1);
    }

    printf("Writing to named shared memory (shared): %s\n", message);
    strncpy((char*)shared_memory_named, message, message_size);

    // 有名共享内存映射，私有
    shared_memory_named = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_named, 0);
    if (shared_memory_named == MAP_FAILED) {
        perror("mmap (named - private)");
        exit(1);
    }

    printf("Writing to named shared memory (private): %s\n", message);
    strncpy((char*)shared_memory_named, message, message_size);

    if (munmap(shared_memory_named, BUFFER_SIZE) == -1) {
        perror("munmap (named)");
        exit(1);
    }

    if (close(fd_named) == -1) {
        perror("close (named)");
        exit(1);
    }

    // 匿名共有内存映射
    shared_memory_anonymous = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_memory_anonymous == MAP_FAILED) {
        perror("mmap (anonymous)");
        exit(1);
    }

    printf("Writing to anonymous shared memory (shared): %s\n", message);
    strncpy((char*)shared_memory_anonymous, message, message_size);

    // 匿名私有内存映射
    shared_memory_anonymous = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (shared_memory_anonymous == MAP_FAILED) {
        perror("mmap (anonymous - private)");
        exit(1);
    }

    printf("Writing to anonymous shared memory (private): %s\n", message);
    strncpy((char*)shared_memory_anonymous, message, message_size);

    if (munmap(shared_memory_anonymous, BUFFER_SIZE) == -1) {
        perror("munmap (anonymous)");
        exit(1);
    }

    return 0;
}
