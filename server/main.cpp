#include "../include/socket/Socket.h"

#include <iostream>

int main()
{
    try
    {
        Socket socket;
        socket.create();
        std::cout << "Socket created. FD = "<< socket.getFd() << '\n';
        socket.bind(6379);
        std::cout<< "Bound to port 6379\n";
        socket.listen(128);
        std::cout << "Listening on port 6379\n";

        int clientFd = socket.accept();
        std::cout<< "Client connected. FD = "<< clientFd<< '\n';
    }
    catch (const std::exception& e)
    {
        std::cerr
            << "Error: "
            << e.what()
            << '\n';

        return 1;
    }

    return 0;
}