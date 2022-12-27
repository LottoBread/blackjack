#ifndef DECK_H
#define DECK_H

class Deck
{
    private: // these variables are only visible to the object
        bool dealtCards[52] = {0}; // bitmap of deck
        int deckSize = 52;
    public:  // these functions/variables can be accessed by anyone 
        int drawCard(); // modifies dealtCards
        // void decrementDeckSize();  
        int getDeckSize(); 
};

#endif 