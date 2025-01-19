#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
 
class TcpServer {
public:
    TcpServer(int port);
    void start();
private:
    int serverSocket;
    struct sockaddr_in serverAddress;
};
 
TcpServer::TcpServer(int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
}
 
void TcpServer::start() {
    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("bind failed");
        return;
    }
 
    listen(serverSocket, 3);
 
    while (true) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int connectionSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);
        if (connectionSocket < 0) {
            perror("accept failed");
            continue;
        }
 
        char buffer[1024];
        ssize_t bytesReceived = recv(connectionSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "Received message: " << buffer << std::endl;
            send(connectionSocket, "Message received", 18, 0);
        }
 
        close(connectionSocket);
    }
}
 
class TcpClient {
public:
    TcpClient(std::string address, int port);
    void sendMessage(std::string message);
    std::string receiveMessage();
private:
    int clientSocket;
    struct sockaddr_in serverAddress;
};
 
TcpClient::TcpClient(std::string address, int port) {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, address.c_str(), &serverAddress.sin_addr);
    serverAddress.sin_port = htons(port);
}
 
void TcpClient::sendMessage(std::string message) {
    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("connect failed");
        return;
    }
    send(clientSocket, message.c_str(), message.length(), 0);
}
 
std::string TcpClient::receiveMessage() {
    char buffer[1024];
    ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived < 0) {
        perror("recv failed");
        return "";
    }
    return std::string(buffer, bytesReceived);
}
 
int main() {
    TcpServer server(8080);
    server.start();
 
    TcpClient client("127.0.0.1", 8080);
    client.sendMessage("Hello server!");
    std::string response = client.receiveMessage();
    std::cout << "Response from server: " << response << std::endl;
 
    return 0;
}
