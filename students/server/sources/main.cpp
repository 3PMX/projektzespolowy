// Server side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
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

const char* database = "database.txt";
std::vector<Login> loginData;

void inputData(std::fstream &file, Register* data, std::vector<Login> vec) {
    for(unsigned int i = 0; i < vec.size(); i++) {
        file<<data->username<<" ";
        file<<data->passwd<<"\n";
    }

}

bool fileExist(const char* name) {
    std::fstream file(name);

    if(!file.good()) return false;

    file.close();

    return true;
}

void saveData(const char* name, Register* data, const std::vector<Login> vec) {
    std::fstream file(name, std::ios::app | std::ios::ate);

    if(!file.good()) {
        printf("Nie mozna otworzyc bazy danych!\n");
        exit(EXIT_FAILURE);
    }
    inputData(file,data, vec);
    file.close();
}

std::vector<Login> readData(const char* name) {
    
    std::vector<Login> data;

    std::fstream file(name, std::ios::in);

    if(!file.good()) {
        printf("Błąd podczas próby dostępu do bazy danych!\n");
        exit(EXIT_FAILURE);
    }

    Login tempData;

    while(!file.eof()) {
        
        file>>tempData.username;
        file>>tempData.passwd;
    
        data.push_back(tempData);
    }
    return data;
}

void clientHandler(int new_socket) {
    printf("Polaczono!\n");

    char buffer[1024];

    
    recv(new_socket, buffer, 1024, 0);

    Header* receiveMsg = (Header*)buffer;
    Header* msg;
    unsigned int msgSize;
    //std::cout<< receiveMsg->msgID <<std::endl;
    //std::cout<< receiveMsg->contentSize <<std::endl;

    std::vector<Login> user = readData(database);
    std::cout<< user[0].username<< " " << user[0].passwd;

    if(receiveMsg->msgID == 1) {
        
        char error[128] = "Podano nieprawidłowe dane!\n";
        char success[128] = "Zalogowano pomyślnie!\n";
        msgSize = sizeof(Header) * sizeof(Login) - sizeof(char);

        Login* receivePayload = (Login*)(receiveMsg->payload);

        for(unsigned int i = 0;i < user.size(); i++) {
            Login userInfo = user.at(i);

            if((receivePayload->username != userInfo.username) && (receivePayload->passwd != userInfo.passwd)) {

                msg = (Header*)malloc(msgSize);

                memcpy(msg->payload, &error, sizeof(error));
                
                send(new_socket, (char*)msg, msgSize, 0);
                break;
            }
            else {

                msg = (Header*)malloc(msgSize);

                memcpy(msg->payload, &success, sizeof(success));
                
                send(new_socket, (char*)msg, msgSize, 0);
                break;

                printf("Ktos zalogował sie\nDane logowania:\n");
        
                std::cout<< receivePayload->username <<std::endl;
                std::cout<< receivePayload->passwd <<std::endl;
            }
        }

        
    }
    else if(receiveMsg->msgID == 2) {
        

        Register* receivePayload = (Register*)(receiveMsg->payload);

        char error[128] = "Taki użytkownik już istnieje!\n";
        char success[128] = "Zarejestrowano pomyślnie!\n";

        for(unsigned int i = 0; i <user.size(); i++) {
            Login userInfo = user.at(i);

            if(receivePayload->username != userInfo.username) {

                Login loginInfo;

                msg = (Header*)malloc(msgSize);

                printf("Ktos zarejestrowal sie\nDane rejestracji:\n");
                std::cout<< receivePayload->username <<std::endl;
                std::cout<< receivePayload->passwd <<std::endl;

                memcpy(&loginInfo, msg->payload, sizeof(Login));

                loginData.push_back(loginInfo);

                memcpy(msg->payload, &success, sizeof(success));
                
                send(new_socket, (char*)msg, msgSize, 0);

                break;
            }
            else {

                msg = (Header*)malloc(msgSize);

                memcpy(msg->payload, &error, sizeof(error));
                
                send(new_socket, (char*)msg, msgSize, 0);
                break;
            }
        }
    }

}

int main(int argc, char const *argv[])
{
    int server_fd, new_socket;
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
    if(!fileExist(database)) {
        printf("Brak bazy danych!!!\n");
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

