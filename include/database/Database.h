#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "Entry.h"

class Database
{
private:
std::unordered_map<
    std::string,
    Entry
> data_;

public:
    bool set(
        const std::string& key,
        const std::string& value);

    std::string get(
        const std::string& key) const;

    bool del(const std::string& key);
    bool exists(const std::string& key) const;
    std::vector<std::string> keys() const;
    void clear();

    bool expire(
    const std::string& key,
    int seconds);
    
};