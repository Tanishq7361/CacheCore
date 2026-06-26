#include "../../include/parser/RespParser.h"

#include <sstream>
#include <vector>
#include <stdexcept>

Command RespParser::parse(
    const std::string& input) const
{
    Command command;

    std::istringstream stream(input);

    std::vector<std::string> lines;

    std::string line;

    while (std::getline(stream, line))
    {
        if (!line.empty() && line.back() == '\r')
        {
            line.pop_back();
        }

        lines.push_back(line);
    }

    if (lines.empty())
    {
        return command;
    }

    if (lines[0].empty() || lines[0][0] != '*')
    {
        throw std::runtime_error("Invalid RESP array");
    }

    for (std::size_t i = 2; i < lines.size(); i += 2)
    {
        if (i == 2)
        {
            command.name = lines[i];
        }
        else
        {
            command.arguments.push_back(lines[i]);
        }
    }

    return command;
}