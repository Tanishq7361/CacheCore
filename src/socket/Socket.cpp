#include "../../include/socket/Socket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>

Socket::Socket()
    : fd_(-1)
{
}

Socket::~Socket()
{
    if (fd_ != -1)
    {
        close(fd_);
    }
}

void Socket::create()
{
    fd_ = socket(AF_INET, SOCK_STREAM, 0);

    if (fd_ == -1)
    {
        throw std::runtime_error(
            std::string("Failed to create socket: ") +
            std::strerror(errno)
        );
    }
}

int Socket::getFd() const
{
    return fd_;
}