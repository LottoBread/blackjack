#ifndef CLIENT_H
#define CLIENT

#include <vector>

using namespace std;

class Client
{
    private: // these variables are only visible to the object
        int fd; // file descriptor for this client
        vector<int> hand;
    
    public: // these functions/variables can be accessed by anyone 
        Client(int fd); // a Constructor that sets the fd variable of this object
        const vector<int>& getHand() const; // returns a reference to the hand that CANNOT be modified
        void addCardToHand(int cardValue);
};

#endif