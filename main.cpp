#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <ctime>

using namespace std;
//string sign[] = { "Diamonds", "Hearts", "Clubs", "Spades" };
string value[] = { "Ace", "Two", "Three","Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };

int cardDeal()
{
    int cardValue = 1+(rand() % 13);
    srand(time(0));
        return cardValue;
}

string randomcard()
{
    string card;
    card = value[cardDeal()];
        return card;

}

int clip()
{
    int lowestCard = 1;
    int highestCard = 10;
        return std::max(lowestCard, std::min(cardDeal()+1, highestCard));
}

int main()
{
    cardDeal();
    int numberofcards = 52;
    int trueValue = clip();
    cout << "You drew a " << randomcard() << endl << trueValue << endl;
}