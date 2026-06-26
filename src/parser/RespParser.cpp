#include "../../include/parser/RespParser.h"

#include <sstream>
#include <vector>

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

    return command;
}