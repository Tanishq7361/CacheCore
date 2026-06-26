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
        std::cout << "Command = [" << command.name << "]\n";

        for (const auto& arg : command.arguments)
        {
            std::cout << "Arg = [" << arg << "]\n";
        }

        if (command.name == "SET")
        {
            if (command.arguments.size() != 2)
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR invalid SET command\n"
                );

                continue;
            }

            database_.set(
                command.arguments[0],
                command.arguments[1]);

            socket_.sendMessage(
                clientFd_,
                "OK\n"
            );
        }
        else if (command.name == "GET")
        {
            if (command.arguments.size() != 1)
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR invalid GET command\n"
                );

                continue;
            }

            std::string value =
                database_.get(
                    command.arguments[0]);

            socket_.sendMessage(
                clientFd_,
                value + "\n"
            );
        }
        else if (command.name == "DEL")
        {
            if (command.arguments.size() != 1)
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR invalid DEL command\n"
                );

                continue;
            }

            bool deleted =
                database_.del(command.arguments[0]);

            socket_.sendMessage(
                clientFd_,
                deleted ? "1\n" : "0\n"
            );
        }
        else
        {
            socket_.sendMessage(
                clientFd_,
                "ERR unknown command\n"
            );
        }
    }
}