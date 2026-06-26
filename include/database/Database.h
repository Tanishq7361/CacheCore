#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Entry.h"
#include <mutex>

class Database
{
private:
std::unordered_map<
    std::string,
    Entry
> data_;
mutable std::mutex mutex_;

public:
    bool set(
        const std::string& key,
        const std::string& value);

    std::string get(
        const std::string& key);

    bool del(const std::string& key);
    bool exists(const std::string& key) const;
    std::vector<std::string> keys() const;
    void clear();

    bool expire(
    const std::string& key,
    int seconds);

    bool isExpired(const Entry& entry) const;

    long long ttl(const std::string& key);
};