#include "../../include/executor/CommandExecutor.h"

CommandExecutor::CommandExecutor(Database& database)
    : database_(database)
{
}

std::string CommandExecutor::execute(const Command& command)
{
    if (command.name == "SET")
    {
        if (command.arguments.size() != 2)
        {
            return "ERR invalid SET command\n";
        }

        database_.set(
            command.arguments[0],
            command.arguments[1]);

        return "OK\n";
    }

    else if (command.name == "GET")
    {
        if (command.arguments.size() != 1)
        {
            return "ERR invalid GET command\n";
        }

        return database_.get(command.arguments[0]) + "\n";
    }

    else if (command.name == "DEL")
    {
        if (command.arguments.size() != 1)
        {
            return "ERR invalid DEL command\n";
        }

        return database_.del(command.arguments[0])
               ? "1\n"
               : "0\n";
    }

    else if (command.name == "EXISTS")
    {
        if (command.arguments.size() != 1)
        {
            return "ERR invalid EXISTS command\n";
        }

        return database_.exists(command.arguments[0])
               ? "1\n"
               : "0\n";
    }

    else if (command.name == "KEYS")
    {
        if (!command.arguments.empty())
        {
            return "ERR KEYS takes no arguments\n";
        }

        auto keys = database_.keys();

        if (keys.empty())
        {
            return "(empty)\n";
        }

        std::string response;

        for (const auto& key : keys)
        {
            response += key;
            response += '\n';
        }

        return response;
    }

    else if (command.name == "CLEAR")
    {
        if (!command.arguments.empty())
        {
            return "ERR CLEAR takes no arguments\n";
        }

        database_.clear();

        return "OK\n";
    }

    else if (command.name == "EXPIRE")
    {
        if (command.arguments.size() != 2)
        {
            return "ERR invalid EXPIRE command\n";
        }

        int seconds =
            std::stoi(command.arguments[1]);

        return database_.expire(
                command.arguments[0],
                seconds)
            ? "1\n"
            : "0\n";
    }
    else if (command.name == "TTL")
    {
        if (command.arguments.size() != 1)
        {
            return "ERR invalid TTL command\n";
        }

        return std::to_string(
            database_.ttl(command.arguments[0])
        ) + "\n";
    }
    else if (command.name == "SAVE")
    {
        if (!command.arguments.empty())
        {
            return "ERR SAVE takes no arguments\n";
        }

        bool success =
            serializer_.save(
                database_,
                "cachecore.rdb"
            );

        return success
            ? "OK\n"
            : "ERR failed to save\n";
    }
    else if (command.name == "LOAD")
    {
        if (!command.arguments.empty())
        {
            return "ERR LOAD takes no arguments\n";
        }

        bool success =
            serializer_.load(
                database_,
                "cachecore.rdb"
            );

        return success
            ? "OK\n"
            : "ERR failed to load\n";
    }
    else if (command.name == "PING")
    {
        if (!command.arguments.empty())
        {
            return "ERR PING takes no arguments\n";
        }

        return "PONG\n";
    }
    return "ERR unknown command\n";
}