#include "../../include/parser/CommandParser.h"

#include <sstream>

Command CommandParser::parse(
    const std::string& input) const
{
    Command command;

    std::istringstream stream(input);

    stream >> command.name;

    std::string argument;

    while (stream >> argument)
    {
        command.arguments.push_back(argument);
    }

    return command;
}