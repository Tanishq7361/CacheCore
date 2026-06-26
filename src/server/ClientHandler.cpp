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
        else if (command.name == "EXISTS")
        {
            if (command.arguments.size() != 1)
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR invalid EXISTS command\n"
                );

                continue;
            }

            bool found =
                database_.exists(command.arguments[0]);

            socket_.sendMessage(
                clientFd_,
                found ? "1\n" : "0\n"
            );
        }
        else if (command.name == "KEYS")
        {
            if (!command.arguments.empty())
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR KEYS takes no arguments\n"
                );

                continue;
            }

            auto keys = database_.keys();

            if (keys.empty())
            {
                socket_.sendMessage(
                    clientFd_,
                    "(empty)\n"
                );

                continue;
            }

            std::string response;

            for (const auto& key : keys)
            {
                response += key;
                response += '\n';
            }

            socket_.sendMessage(
                clientFd_,
                response
            );
        }
        else if (command.name == "CLEAR")
        {
            if (!command.arguments.empty())
            {
                socket_.sendMessage(
                    clientFd_,
                    "ERR CLEAR takes no arguments\n"
                );

                continue;
            }

            database_.clear();

            socket_.sendMessage(
                clientFd_,
                "OK\n"
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