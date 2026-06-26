#pragma once

#include "Command.h"

#include <string>

class RespParser
{
public:
    Command parse(const std::string& input) const;
};