// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
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
};

int main(int argc, char const *argv[])
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
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
    
    int choise;
    unsigned int msgSize;
    Header* msg;
    char buffer[1024];

    std::cout<<"Rejestracja - 2\nLogowanie - 1\n";
    std::cin>>choise;

    switch(choise) {
        case 1:
            {
                msgSize = sizeof(Header) * sizeof(Login) - sizeof(char);
        
                Login* loginData = new Login; //= {"Piotrek", "Haslo"};

                msg = (Header*)malloc(msgSize);

                msg->msgID = 1;
                msg->contentSize = sizeof(Login);

                printf("Zaloguj się!\nPodaj swoją nazwę użytkownika (Login):\n");
                std::cin>> loginData->username;
                printf("\nPodaj swoje hasło:\n");
                std::cin>> loginData->passwd;

                memcpy(msg->payload, loginData, sizeof(Login));

                send(sock, (char*)msg, msgSize, 0);

                if(recv(sock, buffer, 1024, 0) > 0) {
                    Header* receiveMsg = (Header*)buffer;
                    
                    std::cout<< receiveMsg->payload <<std::endl;
                }

                break;
            }
        case 2:
            {
                msgSize = sizeof(Header) * sizeof(Register) - sizeof(char);
        
                Register* registerData  = new Register;//= {"user", "passwd", "passwd"}; //

                msg = (Header*)malloc(msgSize);

                msg->msgID = 2;
                msg->contentSize = sizeof(Register);

                printf("Zarejestruj się już teraz!\nPodaj swoją nazwę użytkownika (Login):\n");
                std::cin>>registerData->username;
                printf("Podaj swoje hasło:\n");
                std::cin>>registerData->passwd;
                printf("Podaj ponownie hasło:\n");
                std::cin>>registerData->repasswd;

                if(strcmp(registerData->passwd, registerData->repasswd) != 0) {
                    printf("\nHasła roznią się\n");
                    break;
                }
                else {
                    memcpy(msg->payload, &registerData, sizeof(Register));

                    send(sock, (char*)msg, msgSize, 0);
                }

                break;
            }
        default:
            break;

    }
    
    

    return 0;
}
