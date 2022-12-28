#ifndef SERVER_H
#define SERVER_H

#define BUF_SIZE 1023

#include "Client.h"


int open_server_socket(char* addr, struct sockaddr_in6* sin6, socklen_t *addr_len);

class Server
{
    private:
        int server_fd;
        char buf[BUF_SIZE] = {0};

    public:
        Server(int fd);
        string readFromClient(Client client); // blocking
        void sendToClient(Client client, string str);
};


#endif