// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
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

struct Register {
    char username[128];
    char passwd[128];
    char repasswd[128];
    char email[128];
};

void clientHandler(int new_socket) {
    printf("Polaczono!\n");

    char buffer[1024];
    
    recv(new_socket, buffer, 1024, 0);

    Header* receiveMsg = (Header*)buffer;

    std::cout<< receiveMsg->msgID <<std::endl;
    std::cout<< receiveMsg->contentSize <<std::endl;

    if(receiveMsg->msgID == 1) {
        printf("Ktos zalogował sie\nDane logowania:\n");
        
        Login* receivePayload = (Login*)(receiveMsg->payload);

        std::cout<< receivePayload->username <<std::endl;
        std::cout<< receivePayload->passwd <<std::endl;
    }
    else if(receiveMsg->msgID == 2) {
        printf("Ktos zarejestrowal sie\nDane rejestracji:\n");

        Register* receivePayload = (Register*)(receiveMsg->payload);

        std::cout<< receivePayload->username <<std::endl;
        std::cout<< receivePayload->passwd <<std::endl;
        std::cout<< receivePayload->email <<std::endl;
    }

}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    printf("Serwer odpalony\n");

    while(true) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                        (socklen_t*)&addrlen))<0)	
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::thread tl(clientHandler, new_socket);
        tl.detach();
    }
    
    return 0;
}

