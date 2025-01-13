#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
#define BUF_SIZE 1024
#define PORT 8888
 
int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    int sock_fd;
    char buffer[BUF_SIZE];
 
    // 创建套接字
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1) {
        perror("创建套接字失败");
        exit(EXIT_FAILURE);
    }
 
    // 定义服务器地址结构体
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 
    // 绑定套接字到服务器地址
    if (bind(sock_fd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    printf("UDP聊天服务器正在端口上运行: %d\n", PORT);
    printf("等待用户中...\n");
 
    while (1) {
        addr_len = sizeof(client_addr);
        // 接收数据
        ssize_t recv_len = recvfrom(sock_fd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &addr_len);
        if (recv_len < 0) {
            perror("接受错误");
            break;
        }
        buffer[recv_len] = '\0';
 
        printf("接收信息: %s\n", buffer);
 
        // 群发数据
        const char *broadcast_msg = "群发消息：";
        sendto(sock_fd, broadcast_msg, strlen(broadcast_msg), 0, (struct sockaddr *)&client_addr, addr_len);
        sendto(sock_fd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);
    }
 
    // 关闭套接字
    close(sock_fd);
    return 0;
}
