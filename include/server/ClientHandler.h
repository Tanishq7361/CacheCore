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
    ClientHandler::ClientHandler(
        Socket& socket,
        Database& database,
        int clientFd)
        : socket_(socket),
        database_(database),
        executor_(database),
        clientFd_(clientFd)
    {
    }
    void handle();
};