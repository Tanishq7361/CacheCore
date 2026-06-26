#pragma once

#include <list>
#include <string>
#include <unordered_map>

class LRUCache
{
private:
    using ListIterator = std::list<std::string>::iterator;

    std::size_t capacity_;

    std::list<std::string> usageList_;

    std::unordered_map<
        std::string,
        ListIterator
    > cacheMap_;

    void touch(ListIterator it);

public:
    explicit LRUCache(std::size_t capacity);

    void put(const std::string& key);

    bool contains(const std::string& key) const;
};