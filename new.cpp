#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

bool deck[52] = {false};

string faceValue[] = {"King", "Ace", "Two", "Three","Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen"};
string suit[] = {"Spades", "Clubs", "Hearts", "Diamonds"};
bool dealtCards[52] = {0};
bool replay = 1;
int playerHand[10] = {0};
int dealerHand[10] = {0};

int deal()
{
    sleep(1);
    int gameCard;
    int cardNumber;
    srand(time(0));
    int cardPosition = (rand() % 52);
    cardNumber = cardPosition % 13;
    int cardSuit = (cardPosition - 1) / 13; 
    if(dealtCards[cardPosition] == 1)
        deal();
    else
        dealtCards[cardPosition] = 1;
    return cardNumber;
}
string translateCard()
{
    string card = "faceValue[cardNumber] of suit[cardSuit]";
    return card;

}

int clip()
{
    int lowestCard = 1;
    int highestCard = 10;
        return std::max(lowestCard, std::min(deal()+1, highestCard));
}

bool playerBust()
{
    int playerTotal = playerHand[1] + playerHand[2] + playerHand[3] + playerHand[4] + playerHand[5] + playerHand[6] + playerHand[7] + playerHand[8] + playerHand[9] + playerHand[10];
    if (playerTotal > 21)
        return 1;
    else
        return 0;
}

bool dealerBust()
{
    int dealerTotal = dealerHand[1] + dealerHand[2] + dealerHand[3] + dealerHand[4] + dealerHand[5] + dealerHand[6] + dealerHand[7] + dealerHand[8] + dealerHand[9] + dealerHand[10];
    if (dealerTotal > 21)
        return 1;
    else
        return 0;
}

void playerLose()
{
    cout << "Player Busted! You lose." << endl;
}

void playerWin()
{
    cout << "Dealer busted! You win." << endl;
}


int main()
{
    bool replay = 1;
    string quitInput;
     cout << "~~~~~ Welcome to BlackJack ~~~~~" << endl;
     cout << "Press ENTER to continue..." << endl;

 //while(replay)
 //{
    string hitStay;
    int numRounds = 0;
    int dealerHandTotal;
         getchar();
         dealerHand[1] = clip();
         dealerHand[2] = clip();
         playerHand[1] = clip();
         playerHand[2] = clip();
         dealerHandTotal = dealerHand[1] + dealerHand[2];
         int playerTotal = playerHand[1] + playerHand[2] + playerHand[3] + playerHand[4] + playerHand[5] + playerHand[6] + playerHand[7] + playerHand[8] + playerHand[9] + playerHand[10];

         cout << "Dealer is showing a " << dealerHand[1] << endl << "You have a " << playerHand[1] << " and a " << playerHand[2] << ", with a total of " << playerHand[1] + playerHand[2] << endl << endl;
         cout << "Press H to hit, S to stay" << endl;
         cin >> hitStay;
         bool drawing = 1;
        if(hitStay == "H")
        {
            //playerHand[3] = clip();
            //cout << "You drew a " << playerHand[3] << ". You have a total of " << playerHand[1] + playerHand[2] + playerHand[3] << endl;
            while(drawing == 1)
            {
                int round = 3;
                string yesno;
                playerHand[round] = clip();
                cout << "You drew a " << playerHand[round] << " with a total of " << playerTotal << endl;
                    if(playerBust() == 1)
                        playerLose();
                    else
                {
                    cout << "Draw Again? (Y/N)";
                    cin >> yesno;
                        if (yesno == "Y")
                        {
                            drawing = 1;
                            round = round + 1;
                        }
                        if (yesno == "N")
                            drawing = 0;
                }
                return playerTotal;
            }
            hitStay = "S";
        }
        
        if (hitStay == "S", dealerHandTotal >= 17)
        {
            cout << "Dealer Had a " << dealerHandTotal << endl;
        }
            else
        {
            while(dealerHandTotal < 17)
            {
                int round = 3;
                dealerHand[round] = clip();
                dealerHandTotal = dealerHand[1] + dealerHand[2] + dealerHand[3] + dealerHand[4] + dealerHand[5] + dealerHand[6] + dealerHand[7] + dealerHand[8] + dealerHand[9];
                round = round + 1;
            }
        cout << "Dealer drew to a " << dealerHandTotal << endl;
        }
        
        if (dealerBust() == 1)
            playerWin();
        
        if(playerBust() == 1)
            playerLose();

        //if( playerTotal > dealerHandTotal, dealerBust == 0)
        //    cout << "Player wins!!!!!!!" << endl;
        //else
        //    cout << "Dealer wins!!!!!!" << endl;
        cout << playerTotal;

        

//}
}