#include "../../include/server/Server.h"

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

        while (true)
        {
            std::string message =
                socket_.receive(clientFd);

            if (message.empty())
            {
                std::cout
                << "Client disconnected\n";
                break;
            }
            close(clientFd);
            std::cout
                << "Received: "
                << message
                << '\n';

            socket_.sendMessage(
                clientFd,
                "Message received by CacheCore\n"
            );
        }
    }
}