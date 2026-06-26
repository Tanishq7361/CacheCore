#include "../../include/server/Server.h"
#include "../../include/server/ClientHandler.h"
#include <iostream>
#include <string>

Server::Server(int port)
    : port_(port)
{
}

void Server::start()
{
    socket_.create();

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

    std::cout
        << "Listening on port "
        << port_
        << '\n';

    while (true)
    {
        std::cout
            << "\nWaiting for client...\n";

        int clientFd = socket_.accept();

        std::cout
            << "Client connected\n";

        ClientHandler handler(
            socket_,
            database_,
            clientFd);

        handler.handle();
    }
}