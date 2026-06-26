#pragma once
#include <stdexcept>
#include <sys/socket.h>

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
};