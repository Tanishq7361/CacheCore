#include "../../include/server/ClientHandler.h"

#include <iostream>
#include <string>

ClientHandler::ClientHandler(
    Socket& socket,
    int clientFd)
    : socket_(socket),
      clientFd_(clientFd)
{
}

void ClientHandler::handle()
{
    while (true)
    {
        std::string message =
            socket_.receive(clientFd_);

        if (message.empty())
        {
            std::cout
                << "Client disconnected\n";

            break;
        }

        std::cout
            << "Received: "
            << message
            << '\n';

        socket_.sendMessage(
            clientFd_,
            "Message received by CacheCore\n"
        );
    }
}