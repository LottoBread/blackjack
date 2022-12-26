#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

bool deck[52] = {false};
int HIDDEN_CARD = -999;
int CARD_HEIGHT = 8;
string CARD_GAP = "   ";

const string CARD_TOP = "┌─────────┐";
const string CARD_BOTTOM = "└─────────┘";
const string HIDDEN_CARD_BODY = "│░░░░░░░░░│";
const string CARD_BODY = "│         │";




string cardValues[] = {"K", "A", "1", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q" };
string faceValue[] = {"King", "Ace", "Two", "Three","Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen"};
string suit[] = {"Spades", "Clubs", "Hearts", "Diamonds"};
bool dealtCards[52] = {0};
bool replay = 1;
int playerHand[10] = {0};
int dealerHand[10] = {0};
bool playerWinLose;
bool playerPush;

string cardHeader(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│ " + cardValues[cardIndex+1] + "       │"; 
    return hdr;
}

string cardFooter(int cardIndex)
{
    // takes index of card and gives corresponding value for top of card
    // i.e. K, Q, J, 4, 5, etc.
    string hdr = "│       " + cardValues[cardIndex+1] + " │"; 
    return hdr;
}

void printCards(int cardIndices[], int num_indices)
{
    string cur_line = "";
    for(int lines = 0; lines < CARD_HEIGHT; lines++)
    {
        cur_line = "";
        for(int i = 0; i < num_indices; i++)
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
        cout << cur_line << endl;
    }
}
void initHands()
{
    int i;
    for( i=0; i<= 10; i++ )
    {
    playerHand[i] = {0};
    }

    for( i=0; i<= 10; i++ )
    {
    dealerHand[i] = {0};
    }

    for( i=0; i<= 52; i++ )
    {
    dealtCards[i] = {0};
    }
}

int dealerHandSum()
{
    int total = dealerHand[0] + dealerHand[1] + dealerHand[2] + dealerHand[3] + dealerHand[4] + dealerHand[5] + dealerHand[6] + dealerHand[7] + dealerHand[8] + dealerHand[9] + dealerHand[10];
    
    return total;
}

int playerHandSum()
{
    int total = playerHand[0] + playerHand[1] + playerHand[2] + playerHand[3] + playerHand[4] + playerHand[5] + playerHand[6] + playerHand[7] + playerHand[8] + playerHand[9] + playerHand[10];
    return total;
}

int deal()
{
    //sleep(1);
    int gameCard;
    int cardNumber;
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

    srand(time(0));
    bool replay = 1;

    string quitInput;
    string hitStay;

    // int arr[] = {1, 0};
    // printCards(arr, 2);
    // int arr1[] = {2, 2};
    // printCards(arr1, 2);
    // int arr2[] = {12, HIDDEN_CARD};
    // printCards(arr2, 2);    

    int dealerHandSum();
        cout << "~~~~~ Welcome to BlackJack ~~~~~" << endl;
        cout << "Press ENTER to continue..." << endl << endl;
        getchar();
    int playerBalance = 1000;

 while(replay == 1)
 {
    bool betting = 1;
    int playerBet;
    int dealerHandHidden[10];

    while(betting == 1)
    {
        cout << "Please enter a bet amount. You currently have " << playerBalance << " credits." << endl << endl;
        cin >> playerBet;
        if (playerBalance < playerBet)
        cout << "You don't have that many credits!" << endl << endl;
        else
        betting = 0;
    }
        playerBalance = playerBalance - playerBet;

         dealerHand[0] = clip();
         dealerHand[1] = clip();
         playerHand[0] = clip();
         playerHand[1] = clip();

         dealerHandHidden[0] = dealerHand[0];
         dealerHandHidden[1] = HIDDEN_CARD;
         cout << "Dealer's Hand:" << endl;
         printCards(dealerHandHidden, 2);
         cout <<  endl << "Player's Hand:" << endl;
         printCards(playerHand, 2);  

         cout << "Dealer is showing a " << dealerHand[0] << endl << "You have a " << playerHand[0] << " and a " << playerHand[1] << ", with a total of " << playerHand[0] + playerHand[1] << endl << endl;
         cout << "Press H to hit, S to stay" << endl;
         cin >> hitStay;
         
        if(hitStay == "H")
        {
            bool drawing = 1;
            int round = 2;

            while(drawing == 1 && playerBust() == 0)
            {
                playerHand[round] = clip();
                cout << endl;
                printCards(playerHand, round+1);
                cout << "You drew a " << playerHand[round] << " with a total of " << playerHandSum() << endl << endl;
                    if(playerBust() == 1)
                        cout << "Bust!" << endl << endl;
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
            cout << "Dealer Had a " << dealerHandSum() << endl << endl;
        }
        if (hitStay == "S" && dealerHandSum() < 17)
        {
            int round = 3;
            while(dealerHandSum() < 17)
            {
                dealerHand[round] = clip();
                round = round + 1;
            }
        cout << "Dealer drew to a " << dealerHandSum() << endl << endl;
        }
        
        if (dealerBust() == 1 && playerBust() == 0)
        {
            playerWin();
            playerWinLose = 1;
            playerPush = 0;
        }
        
        if(playerBust() == 1 && dealerBust() == 0)
        {
            playerLose();
            playerWinLose = 0;
            playerPush = 0;
        }

        if(playerHandSum() > dealerHandSum() && dealerBust() == 0 && playerBust() == 0)
        {
            cout << "Player wins!!!!!!!" << endl << endl;
            playerWinLose = 1;
            playerPush = 0;
        }

        if(dealerHandSum() > playerHandSum() && dealerBust() == 0 && playerBust() == 0)
        {
            cout << "Dealer wins!!!!!!" << endl;
            playerWinLose = 0;
            playerPush = 0;
        }

        if (dealerHandSum() == playerHandSum() && dealerBust() == 0 && playerBust() == 0)
        {
            cout << "Push!" << endl;
            playerWinLose = 0;
            playerPush = 1;
        }

        if (dealerBust() == 1 && playerBust() == 1)
        {
            cout << "You Lose!" << endl;
            playerWinLose = 0;
            playerPush = 0;
        }

        if (playerPush == 1 && playerWinLose == 0)
        {
            cout << "You get your " << playerBet << " back." << endl;
            playerBalance = playerBalance + playerBet;
        }

        if (playerWinLose == 1 && playerPush == 0)
        {
            cout << "Dealer pays " << playerBet * 2 << "." << endl;
            playerBalance = playerBalance + playerBet * 2;
        }

        if (playerWinLose == 0 && playerPush == 0)
            cout << "You lost your bet of " << playerBet << "." << endl;

        cout << "Play again? (Y/N)   Balance:" << playerBalance << endl;
        string playAgain;
        cin >> playAgain;
        if(playAgain == "Y")
            replay = 1;
        if(playAgain == "N")
            replay = 0;

        initHands();
    
        

        

}
        
}