#include "../../include/socket/Socket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <netinet/in.h>

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

void Socket::bind(int port)
{
    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (::bind(
            fd_,
            reinterpret_cast<sockaddr*>(&serverAddress),
            sizeof(serverAddress)) == -1)
    {
        throw std::runtime_error(
            std::string("Bind failed: ") +
            std::strerror(errno)
        );
    }
}

void Socket::listen(int backlog)
{
    if (::listen(fd_, backlog) == -1)
    {
        throw std::runtime_error(
            std::string("Listen failed: ") +
            std::strerror(errno)
        );
    }
}

int Socket::accept()
{
    int clientFd = ::accept(fd_, nullptr, nullptr);

    if (clientFd == -1)
    {
        throw std::runtime_error(
            std::string("Accept failed: ") +
            std::strerror(errno)
        );
    }

    return clientFd;
}

int Socket::getFd() const
{
    return fd_;
}