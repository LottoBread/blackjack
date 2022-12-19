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

void deal()
{
   for (int i = 0; i < 52; i++) 
   {
    int cardNumber;
    srand(time(0));
    int cardPosition = (rand() % 52);
    cardNumber = cardPosition % 13;
    int cardSuit = (cardPosition - 1) / 13;

    //cout << cardNumber << endl << cardPosition << endl;
    
    if(dealtCards[cardPosition] == 1)
        cout << "\033[1;31mCard Already Dealt\033[0m\n" << endl;
    else
        cout << faceValue[cardNumber] << " of " << suit[cardSuit] << endl;
        dealtCards[cardPosition] = 1;
    sleep(2);
    //return 0;

    
    
  
   }
}

int main()
{
    //bool replay = 1;
    //string quitInput;
    deal();
    // cout << "~~~~~ Welcome to BlackJack ~~~~~" << endl;
    // cout << "Press ENTER to continue..." << endl;

// while(replay)
// {
//         getchar();
//         cout << "Dealer is showing a 2" << endl << "You have a X and X" << endl << endl;
//         cout << "Press ENTER to continue...";
//         getchar();
//         cout << "You lose" << endl << endl << "Do you want to play again? (Y/N)" << endl;
//         cin >> quitInput;

//         if(quitInput == "y")
//             replay = 1;
//         else
//             replay = 0;

}
//}