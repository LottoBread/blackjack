#include "Client.h"
#include <vector>

using namespace std;

Client::Client(int fd){
    fd = fd;
}

const vector<int>& Client::getHand() const{
    return hand;
}

void Client::addCardToHand(int cardValue){
    hand.push_back(cardValue);
}