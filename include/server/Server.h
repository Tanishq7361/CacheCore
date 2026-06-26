#pragma once

#include "../socket/Socket.h"
#include "../database/Database.h"
#include "../ttl/TTLManager.h"
#include <thread>
#include <vector>
#include "../persistence/Serializer.h"

class Server
{
private:
    Socket socket_;
    Database database_;
    TTLManager ttlManager_;
    int port_;
    std::vector<std::thread> clientThreads_;
    Serializer serializer_;
public:
    explicit Server(int port);

    void start();
};