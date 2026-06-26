#pragma once
#include <stdexcept>
#include <sys/socket.h>
#include <string>

class Socket
{
private:
    int fd_;

public:
    Socket();

    ~Socket();

    void create();

    int getFd() const;

    void bind(int port);

    void listen(int backlog = SOMAXCONN);

    int accept();

    std::string receive(int clientFd);

};