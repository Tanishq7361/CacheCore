#include "../../include/persistence/Serializer.h"

#include <fstream>

bool Serializer::save(
    const Database& database,
    const std::string& filename)
{
    std::ofstream out(
        filename,
        std::ios::binary
    );

    if (!out)
    {
        return false;
    }

    std::size_t count =
        database.data().size();

    out.write(
        reinterpret_cast<const char*>(&count),
        sizeof(count)
    );

    return true;
}