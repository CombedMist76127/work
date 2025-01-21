#include<iostream>
#include<boost/asio.hpp>
#include<boost/thread.hpp>
#include<map>
#include<string>

using boost::asio::ip::tcp;//使用boost库中的asio组件

std::map<tcp::socket::native_handle_type, tcp::socket> clients;

void client_session(tcp::socket &sock) {
    try {
        for (;;) {
            char data[4096];
            boost::system::error_code error;
            size_t len = sock.read_some(boost::asio::buffer(data), error);
            if (error == boost::asio::error::eof)
                break;
            else if (error)
                throw boost::system::system_error(error);
            std::string message(data, len);
 
            //向所有客户端广播消息
            for (auto &client : clients) {
                if (client.first != sock.native_handle()) {
                    client.second.write_some(boost::asio::buffer(message));
                }
            }
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in client_session: " << e.what() << "\n";
    }
}
 
int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 12345));
 
        for (;;) {
            tcp::socket sock(io_service);
            acceptor.accept(sock);
            std::cout << "Client connected.\n";
 
            //将套接字存储在map中以跟踪
            clients[sock.native_handle()] = sock;
 
            boost::thread t(client_session, std::ref(sock));
            t.detach(); //分离以允许线程独立运行
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in main: " << e.what() << "\n";
    }
 
    return 0;
}
