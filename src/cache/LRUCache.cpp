#include "../../include/cache/LRUCache.h"

LRUCache::LRUCache(std::size_t capacity)
    : capacity_(capacity)
{
}

void LRUCache::touch(ListIterator it)
{
    usageList_.splice(
        usageList_.begin(),
        usageList_,
        it
    );
}

bool LRUCache::contains(
    const std::string& key) const
{
    return cacheMap_.find(key) != cacheMap_.end();
}

void LRUCache::put(
    const std::string& key)
{
    auto it = cacheMap_.find(key);

    if (it != cacheMap_.end())
    {
        touch(it->second);
        return;
    }

    usageList_.push_front(key);

    cacheMap_[key] = usageList_.begin();

    if (cacheMap_.size() > capacity_)
    {
        std::string victim =
            usageList_.back();

        usageList_.pop_back();

        cacheMap_.erase(victim);
    }
}