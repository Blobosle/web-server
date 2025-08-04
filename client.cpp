#include "networking/socket.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    int port = 8080;

    if (argc < 2) {
        std::cout << "Using Port 8080 by default\n";
    }
    else {
        port = (long) argv[1];
        std::cout << "Using Port " << port << "\n";
    }

    http::Client client(port, "Hello server! How you doing?");
}
