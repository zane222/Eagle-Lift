#ifndef LUXURY_DRIVER_H
#define LUXURY_DRIVER_H

#include <string>
#include "Driver.h"

using namespace std;

class LuxuryDriver : public Driver {
    private:
        string amenities;
    public:
        string getAmenities() { return amenities; };
        void setAmenities(string newAmenities) { amenities = newAmenities; }

        LuxuryDriver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes, string amenities) : Driver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes), amenities(amenities) { }
        LuxuryDriver(ifstream& fin);

        void edit() override;

        void print() override;

        void save(ofstream& fout) override;
};
#endif