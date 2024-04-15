#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket < 0)
    {
        std::cerr << "Error in creating socket" << std::endl;
        return 1;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = SERVER_PORT;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))<0)
    {
        std::cerr << "Error in bind " << std::endl;
        return 1;
    }

    if(listen(serverSocket, 1) < 0)
    {
        std::cerr << "Error in listening " << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << SERVER_PORT << "..." << std::endl;

    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientSocket < 0) {
        std::cerr << "Error in accepting connection" << std::endl;
        return 1;
    }

    std::cout << "Accepted connection from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

    // Receive data from client
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived < 0) {
        std::cerr << "Error in receiving data" << std::endl;
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    // Echo back to client
    send(clientSocket, buffer, bytesReceived, 0);

    // Close connection
    close(clientSocket);
    close(serverSocket);
    return 0;
}
