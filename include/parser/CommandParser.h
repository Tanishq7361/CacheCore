#pragma once

#include "Command.h"

#include <string>

class CommandParser
{
public:
    Command parse(const std::string& input) const;
};