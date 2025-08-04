#include "networking/socket.hpp"

#include <iostream>

int main(int argc, char **argv) {
    int port = 8080;

    if (argc < 2) {
        std::cout << "Using Port 8080 by default\n";
    }
    else {
        port = atoi(argv[1]);
        std::cout << "Using Port " << port << "\n";
    }

    http::Server server(port, 3000, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!");
}
