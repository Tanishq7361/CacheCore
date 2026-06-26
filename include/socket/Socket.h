#pragma once
#include <stdexcept>

class Socket
{
private:
    int fd_;

public:
    Socket();

    ~Socket();

    void create();

    int getFd() const;
};