

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
#include <string.h>
#include <cstring>

#include "server.h"
#include "blackjack-tcp.h"
#include "Client.h"
#include "Deck.h"

using namespace std;

int CARD_HEIGHT = 8;
int HIDDEN_CARD = -999;
int SMALL_CARD_HEIGHT = 3;

string cardValues[] = {"K", "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q" };
string faceValue[] = {"King", "Ace", "Two", "Three","Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen"};

const string CARD_TOP = "┌─────────┐";
const string CARD_BOTTOM = "└─────────┘";
const string HIDDEN_CARD_BODY = "│░░░░░░░░░│";
const string CARD_BODY = "│         │";
string CARD_GAP = "   ";
string SMALL_CARD_GAP = " ";

const string SMALL_CARD_TOP = "┌───┐";
const string SMALL_CARD_BOTTOM = "└───┘";
const string SMALL_HIDDEN_CARD_BODY = "│░░░│";
    

string cardFooter(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│       " + cardValues[cardIndex+1] + " │"; 
    return hdr;
}

string cardHeader(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│ " + cardValues[cardIndex+1] + "       │"; 
    return hdr;
}

string getCardsStr(vector<int> cardIndices, int num_indices)
{   
    string output = ""; // sum of all cur_lines
    string cur_line = "";
    for(int lines = 0; lines < CARD_HEIGHT; lines++)
    {
        cur_line = "";
        for(int i = 0; i < num_indices; i++) // if we have multiple cards
        {
            if(lines == 0){ // print top of card(s)
                cur_line += CARD_TOP + CARD_GAP;
            }
            else if(lines == CARD_HEIGHT - 1){ // print bottom of card(s)
                cur_line += CARD_BOTTOM + CARD_GAP;
            }
            else if (cardIndices[i] == HIDDEN_CARD){ // print lined body for hidden dealer card
                cur_line += HIDDEN_CARD_BODY + CARD_GAP;
            }
            else if(lines == 1){ // header
                cur_line += cardHeader(cardIndices[i]) + CARD_GAP;
            }
            else if(lines == CARD_HEIGHT - 2){ // footer
                cur_line += cardFooter(cardIndices[i]) + CARD_GAP;
            }
            else{ // blank card body
                cur_line += CARD_BODY + CARD_GAP;
            }
        }
        // save each line of card
        // cout << cur_line << endl;
        output += cur_line + "\n";
    }                    
    return output;
}

string smallCardHeader(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│ " + cardValues[cardIndex+1] + " │"; 
    return hdr;
}

string printSmallCards(vector<int> cardIndices, int num_indices)
{
    string output;
    string cur_line = "";
    for(int lines = 0; lines < SMALL_CARD_HEIGHT; lines++)
    {
        cur_line = "";
        for(int i = 0; i < num_indices; i++)
        {
            if(lines == 0){ // print top of card(s)
                cur_line += SMALL_CARD_TOP + SMALL_CARD_GAP;
            }
            else if(lines == SMALL_CARD_HEIGHT - 1){ // print bottom of card(s)
                cur_line += SMALL_CARD_BOTTOM + SMALL_CARD_GAP;
            }
            else if (cardIndices[i] == HIDDEN_CARD){ // print lined body for hidden dealer card
                cur_line += SMALL_HIDDEN_CARD_BODY + SMALL_CARD_GAP;
            }
            else if(lines == 1){ // header
                cur_line += smallCardHeader(cardIndices[i]) + SMALL_CARD_GAP;
            }
            //else if(lines == SMALL_CARD_HEIGHT - 2){ // footer
            //    cur_line += cardFooter(cardIndices[i]) + CARD_GAP;
            //}
            //else{ // blank card body
            //    cur_line += CARD_BODY + CARD_GAP;
            //}
        }
        output += cur_line + "\n";
    }
return output;
}

int main(int argc, char *argv[])
{
    struct sockaddr_in6 sin6 = {0};
    socklen_t addr_len;
    int numread = 0, server_fd, connfd;
    char * addr;
    vector<Client> clients;
    string input;
    bool waiting = 1;
    char buf[1024] = {0};



    if(argc == 2)
        addr = argv[1];
    else
        addr = NULL;
    server_fd = open_server_socket(addr, &sin6, &addr_len);

    // sets terminal input to not block
    fcntl(0, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);
 


    while(waiting == 1)
    {
        
        // printf("waiting for connection..\n");
        connfd = accept(server_fd, (struct sockaddr*)&sin6, (socklen_t *)&addr_len);
        if (connfd < 0)
            printf("server accept failed...    type done to stop matchmaking.\n");
        else 
        {
            printf("got connection %d\n", connfd);
            // instantiate client object
            Client c(connfd);
            clients.push_back(c);
        }

        // check for escape sequence

        numread = read(0, buf, 4);
        if(numread > 0)
        {
            if(strcmp(buf, "done") == 0)
                break;
        }

        usleep(1000000);        
    }

    // gameplay loop
    Deck deck;
    string cards;

    for(unsigned int i=0; i < clients.size(); i++){
        // deal hand
        clients[i].addCardToHand(deck.drawCard());
        clients[i].addCardToHand(deck.drawCard());
        cards = getCardsStr(clients[i].getHand() , 2);
        strcpy(buf, cards.c_str());
        if(write(clients[i].fd, buf, cards.size()) == 0)
            printf("Failed to write any bytes to %d\n", clients[i].fd);
        // numread = read(clients[i].fd, buf, 20);
        // printf("Read in %d chars: %s\n", numread, buf);
        
    }
    printf("Done printing cards\n");
    
    // start turns
    for(unsigned int i=0; i < clients.size(); i++){
        cards = printSmallCards(clients[i].getHand(), 2);
        for(unsigned int j=0; j < clients.size(); j++){
            if(i == j) // dont send this client his cards again
                continue;
            strcpy(buf, cards.c_str());
            if(write(clients[j].fd, buf, cards.size()) == 0)
                printf("Failed to write any bytes to %d\n", clients[j].fd);        
        }
        // game logic
        printf("Client %d 's turn\n", clients[i].fd);

    }
    
    return 0;        
    
}