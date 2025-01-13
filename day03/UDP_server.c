#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345    // 服务器监听的端口号
#define BUFFER_SIZE 1024  // 缓冲区大小
 
int main() {
    int sockfd;
    char buffer[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    ssize_t n;
 
    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("创建套接字失败");
        exit(EXIT_FAILURE);
    }
 
    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; // 接受任意IP地址
    server_addr.sin_port = htons(PORT); // 端口号转换为网络字节序
 
    // 绑定套接字到指定的IP地址和端口
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("绑定失败");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
 
    printf("UDP服务器已启动，正在监听端口 %d...\n", PORT);
 
    // 循环接收数据
    while (1) {
        addr_len = sizeof(client_addr);
        // 接收数据报
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (n < 0) {
            perror("接收数据失败");
            continue;
        }
 
        buffer[n] = '\0'; // 确保字符串以'\0'结尾
        printf("接收到来自 %s:%d 的消息：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
 
        // 发送响应
        const char *response = "服务器已收到您的消息";
        sendto(sockfd, response, strlen(response), 0, (struct sockaddr *)&client_addr, addr_len);
    }
 
    // 关闭套接字
    close(sockfd);
    return 0;
}
