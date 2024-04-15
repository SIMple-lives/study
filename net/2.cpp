#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        std::cerr << "Error in creating socket" << std::endl;
        return 1;
    }

    // Connect to server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error in connecting to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Send data to server
    std::string message = "Hello, server!";
    send(clientSocket, message.c_str(), message.length(), 0);

    // Receive data from server
    char buffer[BUFFER_SIZE];
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived < 0) {
        std::cerr << "Error in receiving data" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Received data from server: " << std::string(buffer, bytesReceived) << std::endl;

    // Close connection
    close(clientSocket);

    return 0;
}
