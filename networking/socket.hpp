#pragma once

#include <netinet/in.h>
#include <string>

namespace http {

class Host {
    public:
        Host(int);
    protected:
        int fd; /* Server file descriptor */
        struct sockaddr_in addrs{};
};

class Server : Host {
    public:
        Server(int, const size_t, const std::string&);
};

class Client : Host {
    public:
        Client(int, const std::string&);
};


}
