#ifndef CLIENT_H
#define CLIENT

#include <vector>

using namespace std;

class Client
{
    private: // these variables are only visible to the object
       
        vector<int> hand;
    
    public: // these functions/variables can be accessed by anyone 
        int fd; // file descriptor for this client
        Client(int connfd); // a Constructor that sets the fd variable of this object
        const vector<int>& getHand() const; // returns a reference to the hand that CANNOT be modified
        void addCardToHand(int cardValue);
};

#endif