#ifndef RIDES_H
#define RIDES_H

#include <vector>
#include "Ride.h"
#include "Driver.h"
#include "Drivers.h"
#include "Passenger.h"
#include "Passengers.h"

class Rides {
    private:
        vector<Ride*> rides;
        int nextId = 100001; // store the next what the id will be and increment it every time

        unsigned int getIndexOf(Ride* passenger);
    public:
        void add(Ride* ride);

        Ride* searchById(int rideId);

        void print(Ride* ride) { ride->print(); }
        void print(int rideId) { print(searchById(rideId)); };

        void deleteARide(Ride* ride);
        void deleteRidesByStatus(rideStatus status);
        void deleteAllRidesInvolvingAPassenger(Passenger* passenger);
        void deleteAllRidesInvolvingADriver(Driver* passenger);

        void printAll();
        void printAll(rideStatus status);
        void printAll(Passenger* driver);
        void printAll(Driver* driver);

        bool save(ofstream& fout);
        void readSave(ifstream& fin, Passengers* passengers, Drivers* drivers);

        void deallocate();
};
#endif