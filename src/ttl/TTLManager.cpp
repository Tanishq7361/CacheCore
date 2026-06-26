#include "../../include/ttl/TTLManager.h"

#include <chrono>
#include <iostream>

TTLManager::TTLManager(Database& database)
    : database_(database),
      running_(false)
{
}

TTLManager::~TTLManager()
{
    stop();
}

void TTLManager::start()
{
    if (running_)
    {
        return;
    }

    running_ = true;

    worker_ = std::thread(
        &TTLManager::cleanupLoop,
        this
    );
}

void TTLManager::stop()
{
    if (!running_)
    {
        return;
    }

    running_ = false;

    if (worker_.joinable())
    {
        worker_.join();
    }
}

void TTLManager::cleanupLoop()
{
    while (running_)
    {
        database_.removeExpiredKeys();

        std::this_thread::sleep_for(
            std::chrono::seconds(1));
    }
}