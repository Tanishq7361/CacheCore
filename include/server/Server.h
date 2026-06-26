#pragma once

#include "../socket/Socket.h"

class Server
{
private:
    Socket socket_;
    int port_;

public:
    explicit Server(int port);

    void start();
};