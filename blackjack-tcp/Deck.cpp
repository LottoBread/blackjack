#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <cstdio>

#include "Deck.h"

using namespace std;

// void Deck::decrementDeckSize()
// {
//     if (deckSize <= 0){
//         printf("Cannot decrement decksize, current value is %d\n", deckSize);
//     }
//     deckSize -= 1;
// }

Deck::Deck() {}

int Deck::getDeckSize()
{
    return deckSize;
}

int Deck::drawCard()
{
    int cardNumber, cardPosition = rand() % 52;
    cardNumber = cardPosition % 13;
    if(deckSize <= 0) // all cards used
    {
        printf("Deck empty\n");
        return -999;
    }

    while(dealtCards[cardPosition] == 1) // loop thru deck until valid card
    {
        // increment card position, but loop back around if we reach end of deck
        // program could get stuck in inifinite loop here
        cardPosition = (cardPosition + 1) % 52;
    }
    dealtCards[cardPosition] = 1;
    deckSize -= 1;
    return cardNumber;
}



