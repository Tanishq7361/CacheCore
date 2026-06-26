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

    for (const auto& [key, entry] : database.data())
    {
        std::size_t keyLength = key.size();

        out.write(
            reinterpret_cast<const char*>(&keyLength),
            sizeof(keyLength)
        );

        out.write(
            key.data(),
            keyLength
        );

        std::size_t valueLength =
            entry.value.size();

        out.write(
            reinterpret_cast<const char*>(&valueLength),
            sizeof(valueLength)
        );

        out.write(
            entry.value.data(),
            valueLength
        );
    }
    return true;
}

bool Serializer::load(
    Database& database,
    const std::string& filename)
{
    std::ifstream in(
        filename,
        std::ios::binary
    );

    if (!in)
    {
        return false;
    }

    std::size_t count;

    in.read(
        reinterpret_cast<char*>(&count),
        sizeof(count)
    );

    return true;
}