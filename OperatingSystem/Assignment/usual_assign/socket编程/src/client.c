#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *message = "Hello from client";
    char buffer[BUFFER_SIZE] = {0};

    // 创建套接字
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // 将IPv4地址从字符串转换为二进制形式
    if(inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr)) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // 连接服务器
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }

    // 发送消息给服务器
    write(sock, message, strlen(message));
    printf("Message sent to server\n");

    // 读取服务器的响应
    valread = read(sock, buffer, BUFFER_SIZE);
    printf("Received response from server: %s\n", buffer);

    return 0;
}
