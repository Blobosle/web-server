#include "networking/socket.hpp"

int main() {
    http::Server server(8080, 3000, "Hi, I'm server.");
}
