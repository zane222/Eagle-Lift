#ifndef ECONOMY_DRIVER_H
#define ECONOMY_DRIVER_H

#include <string>
#include "Driver.h"

using namespace std;

class EconomyDriver : public Driver {
    private:
        bool isElectric;
    public:
        bool getIsElectric() { return isElectric; }
        void setIsElectric(bool isElectric) { this->isElectric = isElectric; }

        EconomyDriver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes, bool isElectric) : Driver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes), isElectric(isElectric) { };
        EconomyDriver(ifstream& fin);

        void edit() override;

        void print() override;

        void save(ofstream& fout) override;
};
#endif