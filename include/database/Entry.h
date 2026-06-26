#pragma once

#include <chrono>
#include <string>

struct Entry
{
    std::string value;

    bool hasExpiry = false;

    std::chrono::steady_clock::time_point expiryTime;
};