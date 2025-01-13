#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_PORT 12345  // 服务器端口号
#define SERVER_IP "192.163.90.94"  // 服务器IP地址
#define BUFFER_SIZE 1024  // 缓冲区大小
 
int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
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
    server_addr.sin_family = AF_INET;  // 使用IPv4地址
    server_addr.sin_port = htons(SERVER_PORT);  // 设置端口号，转换为网络字节序
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);  // 将IP地址从文本格式转换为二进制格式
 
    // 发送消息到服务器
    const char *message = "Hello, UDP Server!";
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("已向服务器发送消息：%s\n", message);
 
    // 接收服务器的响应
    addr_len = sizeof(server_addr);
    n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (n > 0) {
        buffer[n] = '\0';  // 确保字符串以'\0'结尾
        printf("接收到服务器的响应：%s\n", buffer);
    } else {
        printf("未接收到服务器的响应或接收出错。\n");
    }
 
    // 关闭套接字
    close(sockfd);
    return 0;
}
