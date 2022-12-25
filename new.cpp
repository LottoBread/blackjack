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

void initHands()
{
    int playerHand[10] = {0};
    int dealerHand[10] = {0};
}

int dealerHandSum()
{
    int total = dealerHand[1] + dealerHand[2] + dealerHand[3] + dealerHand[4] + dealerHand[5] + dealerHand[6] + dealerHand[7] + dealerHand[8] + dealerHand[9] + dealerHand[10];
    return total;
}

int playerHandSum()
{
    int total = playerHand[1] + playerHand[2] + playerHand[3] + playerHand[4] + playerHand[5] + playerHand[6] + playerHand[7] + playerHand[8] + playerHand[9] + playerHand[10];
    return total;
}

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
    if (playerHandSum() > 21)
        return 1;
    else
        return 0;
}

bool dealerBust()
{
    if (dealerHandSum() > 21)
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
    int dealerHandSum();
         getchar();
         dealerHand[1] = clip();
         dealerHand[2] = clip();
         playerHand[1] = clip();
         playerHand[2] = clip();

         cout << "Dealer is showing a " << dealerHand[1] << endl << "You have a " << playerHand[1] << " and a " << playerHand[2] << ", with a total of " << playerHand[1] + playerHand[2] << endl << endl;
         cout << "Press H to hit, S to stay" << endl;
         cin >> hitStay;
         
        if(hitStay == "H")
        {
            bool drawing = 1;
            //playerHand[3] = clip();
            //cout << "You drew a " << playerHand[3] << ". You have a total of " << playerHand[1] + playerHand[2] + playerHand[3] << endl;
            int round = 3;

            while(drawing == 1 && playerBust() == 0)
            {
                playerHand[round] = clip();
                cout << "You drew a " << playerHand[round] << " with a total of " << playerHandSum() << endl;
                    if(playerBust() == 1)
                        cout << "Bust!" << endl;
                    else
                    {
                    cout << "Draw Again? (Y/N)";
                    string yesno = "N";
                    cin >> yesno;
                        if (yesno == "Y")
                        {
                            drawing = 1;
                            round = round + 1;
                        }
                        else
                        {
                            drawing = 0;
                            
                        }
            }
            hitStay = "S";
            }
        }
        
        if (hitStay == "S" && dealerHandSum() >= 17)
        {
            cout << "Dealer Had a " << dealerHandSum() << endl;
        }
        if (hitStay == "S" && dealerHandSum() < 17)
        {
            int round = 3;
            while(dealerHandSum() < 17)
            {
                dealerHand[round] = clip();
                round = round + 1;
            }
        cout << "Dealer drew to a " << dealerHandSum() << endl;
        }
        
        if (dealerBust() == 1 && playerBust() == 0)
            playerWin();
        
        if(playerBust() == 1 && dealerBust() == 0)
            playerLose();

        if(playerHandSum() > dealerHandSum() && dealerBust() == 0 && playerBust() == 0) 
            cout << "Player wins!!!!!!!" << endl;

        if(dealerHandSum() > playerHandSum() && dealerBust() == 0 && playerBust() == 0)
            cout << "Dealer wins!!!!!!" << endl;

        if (dealerHandSum() == playerHandSum() && dealerBust() == 0 && playerBust() == 0)
            cout << "Push!" << endl;

        //cout << "Play again? (Y/N)";
        //string playAgain;
        //cin >> playAgain;
        //if(playAgain == "Y")
        //    replay = 1;
        //if(playAgain == "N")
        //    replay = 0;

        //initHands();
        //cout << playerHandSum() << dealerHandSum();
    
        

        

//}
        
}