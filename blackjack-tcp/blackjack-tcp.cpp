

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
#include <netinet/in.h>
#include <unistd.h>

#include "server.h"
#include "blackjack-tcp.h"

using namespace std;

int main(int argc, char *argv[])
{
    struct sockaddr_in6 sin6 = {0};
    socklen_t addr_len;
    int server_fd, connfd;
    char * addr;
    if(argc == 2)
        addr = argv[1];
    else
        addr = NULL;
    server_fd = open_server_socket(addr, &sin6, &addr_len);

    while(1)
    {
        // printf("waiting for connection..\n");
        connfd = accept(server_fd, (struct sockaddr*)&sin6, (socklen_t *)&addr_len);
        if (connfd < 0)
            printf("server accept failed...\n");
        else 
            printf("got connection\n");
        
        usleep(2000000);
        printf("waiting for connection\n");
    }
}