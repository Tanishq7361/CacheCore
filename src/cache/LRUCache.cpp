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