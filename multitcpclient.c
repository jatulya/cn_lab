#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Change this to the server's IP address
#define SERVER_PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    // Communicate with the server
    while (1) {
        printf("Enter message to send to the server: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // Remove newline character from the buffer
        buffer[strcspn(buffer, "\n")] = 0;

        // Send message to the server
        send(sock, buffer, strlen(buffer), 0);
        printf("Message sent to server\n");

        // Receive response from the server
        valread = read(sock, buffer, BUFFER_SIZE);
        buffer[valread] = '\0';
        printf("Server: %s\n", buffer);

        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);
    }

    // Close the socket
    close(sock);

    return 0;
}
