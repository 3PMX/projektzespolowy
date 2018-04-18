// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080

struct Header {
    unsigned int msgID;
    unsigned int contentSize;
    char payload[1];
};

struct Login {
    char username[128];
    char passwd[128];
};

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    printf("Połączono\n");
    
    unsigned int msgSize = sizeof(Header) * sizeof(Login) - sizeof(char);
    
    Login data = {"Piotrek", "Haslo"};
    
    Header* msg = (Header*)malloc(msgSize);

    msg->msgID = 1;
    msg->contentSize = sizeof(Login);

    memcpy(msg->payload, &data, sizeof(Login));

    send(sock, (char*)msg, msgSize, 0);

    return 0;
}
