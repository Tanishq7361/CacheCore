#include "../../include/server/ClientHandler.h"
#include "../../include/parser/CommandParser.h"
#include "../../include/parser/RespParser.h"

#include <iostream>
#include <string>

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

void ClientHandler::handle()
{
    CommandParser commandParser;
    RespParser respParser;
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

        Command command;
        if (!message.empty() && message[0] == '*')
        {
            command = respParser.parse(message);
        }
        else
        {
            command = commandParser.parse(message);
        }

        std::string response =
            executor_.execute(command);

        socket_.sendMessage(
            clientFd_,
            response
        );
        
    }
}