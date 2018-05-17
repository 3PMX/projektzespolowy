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
#include <mutex>
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

struct activeUsers {
    char username[128];
    int socket;
};

const char* database = "database.txt";
std::vector<Login> loginData;
std::vector<activeUsers> users;
std::mutex mtx;

void inputData(std::fstream &file, std::vector<Login> vec) {
    for(unsigned int i = 0; i < vec.size(); i++) {
        file<<vec[i].username<<" "
            <<vec[i].passwd<<"\n";
    }
    vec.clear();
}

bool fileExist(const char* name) {
    std::fstream file(name);

    if(!file.good()) return false;

    file.close();

    return true;
}

void saveData(const char* name, const std::vector<Login> vec) {
    std::fstream file(name, std::ios::app | std::ios::ate);

    if(!file.good()) {
        printf("Nie mozna otworzyc bazy danych!\n");
        exit(EXIT_FAILURE);
    }
    inputData(file, vec);
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
    file.close();

    return data;
}

void clientHandler(int new_socket, std::vector<Login> user) {
    printf("Polaczono!\n");

    char buffer[1024];

    
    recv(new_socket, buffer, 1024, 0);

    Header* receiveMsg = (Header*)buffer;
    Header* msg;
    unsigned int msgSize;
    bool isAuth = false;
    //std::cout<< receiveMsg->msgID <<std::endl;
    //std::cout<< receiveMsg->contentSize <<std::endl;

    if(receiveMsg->msgID == 1) {
        
        char error[128] = "Podano nieprawidłowe dane!\n";
        char success[128] = "Zalogowano pomyślnie!\n";
        msgSize = sizeof(Header) * sizeof(Login) - sizeof(char);

        Login* receivePayload = (Login*)(receiveMsg->payload);

        for(unsigned int i = 0;i < user.size()-1; i++) 
        {
            Login userInfo = user.at(i);
            activeUsers tempUsers;

            //std::cout<<"Porownuje " << userInfo.username << " i " << userInfo.passwd<< std::endl;
            //std::cout<<"Z " << receivePayload->username << " i " << receivePayload->passwd<< std::endl;

            if( ( strcmp(receivePayload->username, userInfo.username) == 0) && ( strcmp(receivePayload->passwd, userInfo.passwd) == 0) )
            {
                mtx.lock();

                strcpy(tempUsers.username, receivePayload->username);
                tempUsers.socket = new_socket;

                users.push_back(tempUsers);

                mtx.unlock();

                msg = (Header*)malloc(msgSize);

                printf("Ktos zalogował sie\nDane logowania:\n");
        
                std::cout<< receivePayload->username <<std::endl;
                std::cout<< receivePayload->passwd <<std::endl;

                memcpy(msg->payload, &success, sizeof(success));
                
                send(new_socket, (char*)msg, msgSize, 0);

                isAuth = true;
                std::cout<<users[0].username<<std::endl;
            }
        }
        if(!isAuth)
        {
            msg = (Header*)malloc(msgSize);
            
            memcpy(msg->payload, &error, sizeof(error));
                
            send(new_socket, (char*)msg, msgSize, 0);
        }

        //free(msg);
        
    }
    else if(receiveMsg->msgID == 2) {
        
        Register* receivePayload = (Register*)(receiveMsg->payload);

        char error[128] = "Taki użytkownik już istnieje!\n";
        char success[128] = "Zarejestrowano pomyślnie!\n";

        for(unsigned int i = 0; !isAuth && i < user.size()-1; i++) {
            Login userInfo = user.at(i);

            //std::cout<<"Porownuje " << userInfo.username << " z " << receivePayload->username<< std::endl;

            isAuth = (strcmp(receivePayload->username, userInfo.username) == 0);
        }

        if(!isAuth) {
            //std::cout<<"Mozesz dodac"<<std::endl;

            Login loginInfo;
            activeUsers tempUsers;

            msg = (Header*)malloc(msgSize);

            printf("Ktos zarejestrowal sie\nDane rejestracji:\n");
            std::cout<< receivePayload->username <<std::endl;
            std::cout<< receivePayload->passwd <<std::endl;

            mtx.lock();

            //memcpy(&loginInfo, msg->payload, sizeof(Login)); --nie działa tak nie wiem czemu :p
            strcpy(loginInfo.username, receivePayload->username);
            strcpy(loginInfo.passwd, receivePayload->passwd);

            strcpy(tempUsers.username, receivePayload->username);
            tempUsers.socket = new_socket;

            users.push_back(tempUsers);
            loginData.push_back(loginInfo);

            saveData(database, loginData);

            mtx.unlock();

            memcpy(msg->payload, &success, sizeof(success));
                
            send(new_socket, (char*)msg, msgSize, 0);

            //std::cout<< loginInfo.username<<std::endl;
            //std::cout<< loginInfo.passwd<<std::endl;

        }
        else {
            //std::cout<<"Nie mozesz dodac"<<std::endl;
            msg = (Header*)malloc(msgSize);

            memcpy(msg->payload, &error, sizeof(error));
                
            send(new_socket, (char*)msg, msgSize, 0);
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

    std::vector<Login> user = readData(database);

    std::cout<<"Server is running"<<std::endl;
    
    for(unsigned int i = 0; i <user.size()-1; i++ ) {
        std::cout<<user[i].username<<" "<<user[i].passwd<<std::endl;
    }
    
    while(true) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                        (socklen_t*)&addrlen))<0)	
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::thread tl(clientHandler, new_socket, user);
        tl.detach();
    }
    
    return 0;
}

