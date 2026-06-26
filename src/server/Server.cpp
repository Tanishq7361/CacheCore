#include "../../include/server/Server.h"
#include "../../include/server/ClientHandler.h"
#include <iostream>
#include <string>

Server::Server(int port)
    : socket_(),
      database_(),
      ttlManager_(database_),
      port_(port)
{
}

void Server::start()
{
    socket_.create();
    serializer_.load(
        database_,
        "cachecore.rdb"
    );
    std::cout
        << "Socket created. FD = "
        << socket_.getFd()
        << '\n';

    socket_.bind(port_);

    std::cout
        << "Bound to port "
        << port_
        << '\n';

    socket_.listen(128);
    ttlManager_.start();

    std::cout
        << "Listening on port "
        << port_
        << '\n';

    while (true)
    {
        int clientFd = socket_.accept();

        std::thread(
            [this, clientFd]()
            {
                ClientHandler handler(
                    socket_,
                    database_,
                    clientFd);

                handler.handle();
            }
        ).detach();
    }
}

