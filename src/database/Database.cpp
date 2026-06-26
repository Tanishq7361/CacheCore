#include "../../include/database/Database.h"
#include <chrono>

bool Database::set(
    const std::string& key,
    const std::string& value)
{
    data_[key].value = value;

    return true;
}

std::string Database::get(
    const std::string& key) 
{
    auto it = data_.find(key);

    if (it == data_.end())
    {
        return "(nil)";
    }

    if (isExpired(it->second))
    {
        data_.erase(it);

        return "(nil)";
    }

    return it->second.value;
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

bool Database::expire(
    const std::string& key,
    int seconds)
{
    auto it = data_.find(key);

    if (it == data_.end())
    {
        return false;
    }

    it->second.hasExpiry = true;

    it->second.expiryTime =
        std::chrono::steady_clock::now() +
        std::chrono::seconds(seconds);

    return true;
}

bool Database::isExpired(const Entry& entry) const
{
    if (!entry.hasExpiry)
    {
        return false;
    }

    return std::chrono::steady_clock::now() >= entry.expiryTime;
}

long long Database::ttl(const std::string& key)
{
    auto it = data_.find(key);

    if (it == data_.end())
    {
        return -2;
    }

    if (isExpired(it->second))
    {
        data_.erase(it);
        return -2;
    }

    if (!it->second.hasExpiry)
    {
        return -1;
    }

    auto remaining =
        std::chrono::duration_cast<std::chrono::seconds>(
            it->second.expiryTime -
            std::chrono::steady_clock::now());

    return remaining.count();
}

void Database::removeExpiredKeys()
{
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = data_.begin();

    while (it != data_.end())
    {
        if (isExpired(it->second))
        {
            it = data_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}