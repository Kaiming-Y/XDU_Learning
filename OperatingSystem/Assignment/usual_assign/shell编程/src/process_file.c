#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main() {
    // 创建子进程
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "进程创建失败\n");
        exit(1);
    } else if (pid == 0) {
        // 子进程
        printf("这是子进程\n");
        // 在这里添加子进程需要执行的代码

        // 示例：创建一个新文件并写入内容
        FILE *file = fopen("example.txt", "w");
        if (file != NULL) {
            fprintf(file, "这是一个示例文件\n");
            fclose(file);
        }

        exit(0);
    } else {
        // 父进程
        printf("这是父进程\n");
        // 在这里添加父进程需要执行的代码
    }

    return 0;
}
