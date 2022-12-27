#ifndef CLIENT_H
#define CLIENT

#define MAX_CARDS 10

class Client
{
    private:
        int fd;
        int hand[MAX_CARDS];
    
    public:
        Client(int connfd);
};

#endif