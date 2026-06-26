#pragma once

#include "../database/Database.h"

#include <string>

class Serializer
{
public:
    bool save(
        const Database& database,
        const std::string& filename);

    bool load(
        Database& database,
        const std::string& filename);
};