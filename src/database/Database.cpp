#include "../../include/database/Database.h"

bool Database::set(
    const std::string& key,
    const std::string& value)
{
    data_[key] = value;

    return true;
}

std::string Database::get(
    const std::string& key) const
{
    auto it = data_.find(key);

    if (it == data_.end())
    {
        return "(nil)";
    }

    return it->second;
}