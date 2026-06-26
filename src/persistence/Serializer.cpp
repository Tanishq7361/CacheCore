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

    for (std::size_t i = 0; i < count; i++)
    {
        std::size_t keyLength;

        in.read(
            reinterpret_cast<char*>(&keyLength),
            sizeof(keyLength)
        );

        std::string key(keyLength, '\0');

        in.read(
            key.data(),
            keyLength
        );

        std::size_t valueLength;

        in.read(
            reinterpret_cast<char*>(&valueLength),
            sizeof(valueLength)
        );

        std::string value(valueLength, '\0');

        in.read(
            value.data(),
            valueLength
        );

        database.set(
            key,
            value
        );
    }

    return true;
}