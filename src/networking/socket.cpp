#include "socket.hpp"

#include <array>
#include <netinet/in.h>
#include <sys/socket.h>
#include <system_error>
#include <string>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>

#define MSG_BUF (3000)
#define ERROR(x) do { \
        std::error_code ec(errno, std::generic_category()); \
        throw std::system_error(ec, x); \
    } while (0)

http::Host::Host(int port) {
    if ((fd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        ERROR("socket() failed");
    }

    addrs.sin_family = AF_INET;
    addrs.sin_port = htons(port);
}

http::Server::Server(int port, const size_t accept_buf, const std::string& reply) : Host(port) {
    addrs.sin_addr.s_addr = htonl(INADDR_ANY);

    if (::bind(fd, reinterpret_cast<struct sockaddr*>(&addrs), sizeof(addrs)) < 0) {
        ERROR("bind() failed");
    }

    if (::listen(fd, 10)) {
        ERROR("listen() failed");
    }

    for (;;) {
        std::cout << "WAITING FOR CONNECTION REQUEST\n";
        int c_socket = 0;

        if ((c_socket = accept(fd,
            reinterpret_cast<struct sockaddr*>(&addrs),
            reinterpret_cast<socklen_t*>(&addrs))) < 0) {
            ERROR("accept() failed");
        }

        std::array<char, MSG_BUF> buffer{0};
        int rd = ::read(c_socket, buffer.data(), buffer.size());

        if (rd == EOF) {
            std::cout << "Client closed the connection\n";
        }
        else if (rd < 0) {
            ERROR("read() failed");
        }

        std::cout << "[to SERVER] " << buffer.data() << std::endl;

        int wr = ::write(c_socket, reply.data(), reply.size());

        if (wr < 0) {
            ERROR("write() failed");
        }

        close(c_socket);
    }
}

http::Client::Client(int port, const std::string& msg) : Host(port) {
    if (::inet_pton(AF_INET, "127.0.0.1", &addrs.sin_addr) <= 0) {
        ERROR("inet failure");
    }

    if (::connect(fd, reinterpret_cast<struct sockaddr*>(&addrs), sizeof(addrs)) < 0) {
        ERROR("connect() failed");
    }

    send(fd, msg.data(), msg.size(), 0);

    std::array<char, 1024> buffer;
    int valread = read(fd, buffer.data(), 1024);

    std::cout << "[from SERVER] " << buffer.data() << std::endl;
}
