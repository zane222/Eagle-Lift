#ifndef RIDE_H
#define RIDE_H

#include <string>
#include <vector>
#include "Passenger.h"
#include "Passengers.h"
#include "Driver.h"
#include "Drivers.h"

using namespace std;

enum rideStatus { active = 'a', completed = 'c', Cancelled = 'C' };

class Ride {
    private:
        int id;
        string pickupLocation;
        time_t pickupTime;
        string dropoffLocation;
        int sizeOfParty;
        bool includesPets;
        time_t dropoffTime;
        rideStatus status;
        float ratingByCustomer;
        Passenger* passenger;
        Driver* driver;

        string convertStatusToString(rideStatus status);
    public:
        int getId() { return id; }
        void setId(int newId) { id = newId; }
    
        string getPickupLocation() { return pickupLocation; }
        void setPickupLocation(string newPickupLocation) { pickupLocation = newPickupLocation; }
    
        time_t getPickupTime() { return pickupTime; }
        void setPickupTime(time_t newPickupTime) { pickupTime = newPickupTime; }
    
        string getDropoffLocation() { return dropoffLocation; }
        void setDropoffLocation(string newDropoffLocation) { dropoffLocation = newDropoffLocation; }
    
        int getSizeOfParty() { return sizeOfParty; }
        void setSizeOfParty(int newSizeOfParty) { sizeOfParty = newSizeOfParty; }
    
        bool getIncludesPets() { return includesPets; }
        void setIncludesPets(bool newIncludesPets) { includesPets = newIncludesPets; }
    
        time_t getDropoffTime() { return dropoffTime; }
        void setDropoffTime(time_t newDropoffTime) { dropoffTime = newDropoffTime; }
    
        rideStatus getStatus() { return status; }
        void setStatus(rideStatus newStatus) { status = newStatus; }
    
        float getRatingByCustomer() { return ratingByCustomer; }
        void setRatingByCustomer(float newRatingByCustomer) { ratingByCustomer = newRatingByCustomer; }

        Passenger* getPassenger() { return passenger; }
        void setPassenger(Passenger* newPassenger) { passenger = newPassenger; }

        Driver* getDriver() { return driver; }
        void setDriver(Driver* newDriver) { driver = newDriver; }

        Ride(Passenger* passenger, Driver* driver, time_t rideCreationTime, int estimatedTimeUntilPickupMinutes, int estimatedTimeOfRideMinutes, string pickupLocation, string dropoffLocation, int sizeOfParty, bool includesPets);
        Ride(ifstream& fin, Passengers* passengers, Drivers* drivers);

        void print();

        void save(ofstream& fout);

        bool operator == (Ride& otherRide) { return id == otherRide.getId(); }
};
#endif