#pragma once

#include "../database/Database.h"

#include <atomic>
#include <thread>

class TTLManager
{
private:
    Database& database_;

    std::thread worker_;

    std::atomic<bool> running_;

public:
    explicit TTLManager(Database& database);

    ~TTLManager();

    void start();

    void stop();

private:
    void cleanupLoop();
};