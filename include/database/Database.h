#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class Database
{
private:
    std::unordered_map<
        std::string,
        std::string
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
};