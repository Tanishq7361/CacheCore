#pragma once

#include "../socket/Socket.h"
#include "../database/Database.h"
#include "../executor/CommandExecutor.h"

class ClientHandler
{
private:
    Socket& socket_;
    Database& database_;
    CommandExecutor executor_;
    int clientFd_;

public:
    ClientHandler(
        Socket& socket,
        Database& database,
        int clientFd);

    void handle();
};