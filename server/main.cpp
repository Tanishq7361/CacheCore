#include "../include/socket/Socket.h"

#include <iostream>
#include <string>

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

       std::cout << "Waiting for client...\n";

        int clientFd = socket.accept();

        std::cout << "Client connected\n";

        std::cout << "Waiting for message...\n";

        std::string message =
            socket.receive(clientFd);

        std::cout << "Received message\n";
        std::cout
            << "Received: "
            << message
            << '\n';

        socket.sendMessage(
            clientFd,
            "Message received by CacheCore\n"
        );
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