#pragma once

#include "../socket/Socket.h"
#include "../database/Database.h"
#include "../ttl/TTLManager.h"

class Server
{
private:
    Socket socket_;
    Database database_;
    TTLManager ttlManager_;
    int port_;

public:
    explicit Server(int port);

    void start();
};