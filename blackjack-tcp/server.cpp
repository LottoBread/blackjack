
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "Client.h"
#include "server.h"

Server::Server(int fd)
{
    server_fd = fd;
}

string Server::readFromClient(Client client)
{
    memset(buf, 0, BUF_SIZE);
    // need to handle case where morer than BUFSIZE bytes are read
    read(client.fd, buf, BUF_SIZE);
    string output = buf;
    return output;
}

void Server::sendToClient(Client client, string str){
    memset(buf, 0, BUF_SIZE);
    strcpy(buf, str.c_str());
    write(client.fd, buf, BUF_SIZE);

}


void ipv4str_to_ipv6(char* v4, uint8_t* v6)
{
    int v4_addr[4], i = 0;
    char * tokens = strtok(v4, " .");
    while(tokens != NULL)
    {
        // printf("_%s_", tokens);
        v4_addr[i] = atoi(tokens);
        tokens = strtok(NULL, " .");
        i++;
    }
    // for(i=0; i<4;i++)
    //     printf(" %d ", v4_addr[i]);
    v6[10] = 0xff;
    v6[11] = 0xff;
    v6[12] = v4_addr[0];
    v6[13] = v4_addr[1];
    v6[14] = v4_addr[2];
    v6[15] = v4_addr[3];
}

bool SetSocketBlockingEnabled(int fd, bool blocking)
{
   if (fd < 0) return false;

#ifdef _WIN32
   unsigned long mode = blocking ? 0 : 1;
   return (ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
#else
   int flags = fcntl(fd, F_GETFL, 0);
   if (flags == -1) return false;
   flags = blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
   return (fcntl(fd, F_SETFL, flags) == 0) ? true : false;
#endif
}

int open_server_socket(char* addr, struct sockaddr_in6* sin6, socklen_t *addr_len)
{
    int  sock_bind, server_fd, no = 0;

    struct in6_addr anyaddr = IN6ADDR_ANY_INIT;
    *addr_len = sizeof(sin6);
    //int i = 0;
    
    if((server_fd = socket(AF_INET6, SOCK_STREAM | SOCK_NONBLOCK, 0)) <  0)
    {
        printf("failed to create socket\n");
        return 1;
    } 

    if((setsockopt(server_fd, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&no, sizeof(no))))
    {
        printf("failed to set socket option\n");
        return 1;    
    }


    sin6->sin6_family = AF_INET6;
    sin6->sin6_flowinfo = 0;
    sin6->sin6_port = htons(6969);
    if(addr)
    {
        if(inet_pton(AF_INET6, addr, (void*)&(sin6->sin6_addr)) != 1) // try ipv6 conversion
        {
            ipv4str_to_ipv6(addr, (uint8_t*)&(sin6->sin6_addr));
        }
    }
    else
        sin6->sin6_addr = anyaddr;
    // printf("address is: ");
    // ipv6_to_str_unexpanded(&(sin6.sin6_addr));
    if((sock_bind = bind(server_fd, (struct sockaddr*)sin6, sizeof(*sin6))) < 0)
    {
        printf("failed to bind socket %d\n", sock_bind);
        return 1;
    }

    if(getsockname(server_fd, (struct sockaddr*)sin6, addr_len))
    {
        printf("failed to get socket name\n");
        return 1;
    }

    printf("HTTP server is using TCP port %d\n", ntohs(sin6->sin6_port));
    fflush(stdout);

    if(listen(server_fd, 10))
    {
        printf("failed to listen\n");
        return 1;
    }
    return server_fd;
}