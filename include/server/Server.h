#pragma once

#include "../socket/Socket.h"
#include "../database/Database.h"

class Server
{
private:
    Socket socket_;
    int port_;
    Database database_;

public:
    explicit Server(int port);

    void start();
};