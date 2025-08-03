#include "networking/socket.hpp"

int main() {
    http::Client client(8080, "Hello server! How you doing?");
}
