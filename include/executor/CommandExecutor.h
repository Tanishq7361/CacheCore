#pragma once

#include "../database/Database.h"
#include "../parser/Command.h"
#include "../persistence/Serializer.h"

#include <string>

class CommandExecutor
{
private:
    Database& database_;
    Serializer serializer_;

public:
    explicit CommandExecutor(Database& database);

    std::string execute(const Command& command);
};