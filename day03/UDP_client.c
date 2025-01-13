#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
 
#define BUF_SIZE 1024
#define SERVER_IP "192.168.90.94"
#define SERVER_PORT 8080
 
void *send_thread(void *);
void *recv_thread(void *);
 
int sock_fd;
struct sockaddr_in server_addr;
 
int main(int argc, char *argv[]) {
    pthread_t send_tid, recv_tid;
    int err;
 
    // 初始化套接字地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
 
    // 创建UDP套接字
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("创建套接字失败");
        exit(EXIT_FAILURE);
    }
 
    // 创建发送线程
    err = pthread_create(&send_tid, NULL, send_thread, NULL);
    if (err != 0) {
        perror("无法创建发送线程");
        exit(EXIT_FAILURE);
    }
 
    // 创建接收线程
    err = pthread_create(&recv_tid, NULL, recv_thread, NULL);
    if (err != 0) {
        perror("无法创建接收线程");
        exit(EXIT_FAILURE);
    }
 
    // 等待线程完成
    pthread_join(send_tid, NULL);
    pthread_join(recv_tid, NULL);
 
    // 关闭套接字
    close(sock_fd);
 
    return 0;
}
 
void *send_thread(void *data) {
    char send_buf[BUF_SIZE];
    while (1) {
        printf("输入信息 (输入“exit”取消): ");
        fgets(send_buf, BUF_SIZE, stdin);
        if (!strncmp(send_buf, "exit", 4)) {
            break;
        }
        sendto(sock_fd, send_buf, strlen(send_buf), 0, 
               (struct sockaddr *)&server_addr, sizeof(server_addr));
    }
    pthread_exit(NULL);
}
 
void *recv_thread(void *data) {
    char recv_buf[BUF_SIZE];
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    int recv_len;
    while (1) {
        addr_len = sizeof(server_addr);
        recv_len = recvfrom(sock_fd, recv_buf, BUF_SIZE, 0, 
                            (struct sockaddr *)&server_addr, &addr_len);
        if (recv_len < 0) {
            perror("接收错误");
            continue;
        }
        recv_buf[recv_len] = '\0';
        printf("接收信息：%s\n", recv_buf);
    }
    pthread_exit(NULL);
}
