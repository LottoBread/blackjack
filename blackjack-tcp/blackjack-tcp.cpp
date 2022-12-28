

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

//string spades = "\u2660";
//string hearts = "\u2665";
//string diamonds = "\u2666";
//string clubs = "\u2663";


int CARD_HEIGHT = 8;
int HIDDEN_CARD = -999;
int SMALL_CARD_HEIGHT = 3;

string cardValues[] = {"K", "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q" };
string faceValue[] = {"King", "Ace", "Two", "Three","Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen"};
string cardSuit[] = {"\u2660", "\u2665", "\u2666", "\u2663" };
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
    // takes index of card and gives corresponding value for top of cardoill
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│ " + cardSuit[rand() % 4] + "     " + cardValues[cardIndex+1] + " │"; 
    return hdr;
}

string cardHeader(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│ " + cardValues[cardIndex+1] + "     " + cardSuit[rand() % 4] + " │"; 
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
            //else if(lines == 4){ // suit
            //    cur_line += cardSuit() + CARD_GAP;
            //}
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
    setlocale(LC_ALL, "");
    //cout << "\u2660" << endl;

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
    Server server(server_fd);
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
        memset(buf, 0, 1024);
        
    }
    printf("Done printing cards\n");
    
    // start turns
    for(unsigned int i=0; i < clients.size(); i++){
        cards = printSmallCards(clients[i].getHand(), 2);
        for(unsigned int j=0; j < clients.size(); j++){
            if(i == j) // dont send this client his cards again
                continue;
            if(write(clients[j].fd, buf, cards.size()) == 0)
                printf("Failed to write any bytes to %d\n", clients[j].fd);        
        }
        // game logic
        printf("Client %d 's turn\n", clients[i].fd);

        // memset(buf, 0, 1024);
        //numread = read(clients[i].fd, buf, 255);
        //if(numread > 0)
        //{
        //cout << buf;
        //}


        while(clients[i].hitStay == 1){
            server.sendToClient(clients[i], "Would you like to hit? (Yes/No) \n");
            string hit = server.readFromClient(clients[i]);
            string yes = "Yes\n";
            //cout << hit;
                if(hit == yes){
                server.sendToClient(clients[i], "You hit");
                cout << hit;
                }
                else{
                server.sendToClient(clients[i], "You stay");
                clients[i].hitStay = 0;
                cout << hit;
                }
        }

        

    }
    
    //return 0;        
    
}