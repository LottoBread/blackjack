#ifndef SERVER_H
#define SERVER_H

int open_server_socket(char* addr, struct sockaddr_in6* sin6, socklen_t *addr_len);

#endif