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
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
            std::string message(data, len);
 
            // Broadcast message to all clients.
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
 
            // Store the socket in a map to keep track of it.
            clients[sock.native_handle()] = sock;
 
            boost::thread t(client_session, std::ref(sock));
            t.detach(); // Detach to allow the thread to run independently.
        }
    } catch (std::exception &e) {
        std::cerr << "Exception in main: " << e.what() << "\n";
    }
 
    return 0;
}
