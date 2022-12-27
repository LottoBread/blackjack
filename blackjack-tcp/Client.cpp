#include "Client.h"
#include <vector>

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