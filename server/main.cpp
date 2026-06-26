#include "../include/socket/Socket.h"

#include <iostream>

int main()
{
    try
    {
        Socket socket;
        socket.create();
        socket.bind(6379);
        std::cout<< "Bound to port 6379\n";
        std::cout << "Socket created. FD = "<< socket.getFd() << '\n';
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