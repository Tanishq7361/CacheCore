#pragma once

#include "../socket/Socket.h"

class ClientHandler
{
private:
    Socket& socket_;
    int clientFd_;

public:
    ClientHandler(
        Socket& socket,
        int clientFd);

    void handle();
};