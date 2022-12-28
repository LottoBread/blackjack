#include "Client.h"
#include <vector>
#include <iostream>
#include <numeric>

using namespace std;

Client::Client(int connfd){
    fd = connfd;
}

const vector<int>& Client::getHand() const{
    return hand;
}

void Client::addCardToHand(int cardValue){
    hand.push_back(cardValue);
}

int Client::getHandSum(Client client){
    //int total = 0;
    //total = client.hand[0] + client.hand[1] + client.hand[2] + client.hand[3] + client.hand[4] + client.hand[5] + client.hand[6] + client.hand[7] + client.hand[8] + client.hand[9];
    int total = 0;
    total = accumulate(client.hand.begin(), client.hand.end(), decltype(client.hand)::value_type(0)) + 1;
    return total;
}