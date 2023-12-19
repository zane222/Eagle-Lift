#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include "User.h"

using namespace std;

enum payment { cash = 'c', CreditCard = 'C', payPal = 'p', other = 'o' };

class Passenger : public User {
    private:
        payment paymentPreference;
        bool handicapped;
        float defaultRatingRequired;
        bool hasPets;
    public:
        payment getPaymentPreference() { return paymentPreference; }
        void setPaymentPreference(payment newPaymentPreference) { paymentPreference = newPaymentPreference; }
    
        bool getHandicapped() { return handicapped; }
        void setHandicapped(bool newHandicapped) { handicapped = newHandicapped; }
    
        float getDefaultRatingRequired() { return defaultRatingRequired; }
        void setDefaultRatingRequired(float newDefaultRatingRequired) { defaultRatingRequired = newDefaultRatingRequired; }
    
        bool getHasPets() { return hasPets; }
        void setHasPets(bool newHasPets) { hasPets = newHasPets; }
    
        Passenger(string name, payment paymentPreference, bool handicapped, float defaultRatingRequired, bool hasPets);
        Passenger(ifstream& fin);
    
        void print();
    
        void edit();

        void save(ofstream& fout);
};
#endif