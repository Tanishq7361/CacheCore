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

bool Database::del(const std::string& key)
{
    return data_.erase(key) > 0;
}

bool Database::exists(const std::string& key) const
{
    return data_.find(key) != data_.end();
}

std::vector<std::string> Database::keys() const
{
    std::vector<std::string> result;

    result.reserve(data_.size());

    for (const auto& [key, value] : data_)
    {
        result.push_back(key);
    }

    return result;
}

void Database::clear()
{
    data_.clear();
}