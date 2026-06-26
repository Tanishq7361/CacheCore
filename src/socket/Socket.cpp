#include "../../include/socket/Socket.h"

#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <netinet/in.h>
#include <string>

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
    int opt = 1;

    if (setsockopt(
            fd_,
            SOL_SOCKET,
            SO_REUSEADDR,
            &opt,
            sizeof(opt)) == -1)
    {
        throw std::runtime_error(
            std::string("setsockopt failed: ") +
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

std::string Socket::receive(int clientFd)
{
    char buffer[1024];

    ssize_t bytesReceived =
        recv(clientFd,
             buffer,
             sizeof(buffer) - 1,
             0);

    if (bytesReceived == -1)
    {
        throw std::runtime_error(
            std::string("Receive failed: ") +
            std::strerror(errno)
        );
    }

    buffer[bytesReceived] = '\0';

    std::string msg(buffer);
    return msg;
}
void Socket::sendMessage(
    int clientFd,
    const std::string& message)
{
    ssize_t bytesSent =
        send(clientFd,
             message.c_str(),
             message.size(),
             0);

    if (bytesSent == -1)
    {
        throw std::runtime_error(
            std::string("Send failed: ") +
            std::strerror(errno)
        );
    }
}
