#include "../../include/server/ClientHandler.h"
#include "../../include/parser/CommandParser.h"

#include <iostream>
#include <string>

ClientHandler::ClientHandler(
    Socket& socket,
    Database& database,
    int clientFd)
    : socket_(socket),
      database_(database),
      clientFd_(clientFd)
{
}

void ClientHandler::handle()
{
    CommandParser parser;
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

        Command command =
            parser.parse(message);

        std::string response =
            executor_.execute(command);

        socket_.sendMessage(
            clientFd_,
            response
        );
        
    }
}