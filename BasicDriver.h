#ifndef BASIC_DRIVER_H
#define BASIC_DRIVER_H

#include <string>
#include "Driver.h"

using namespace std;

class BasicDriver : public Driver {
    private:
        int rustiness; // scale of 1-10
    public:
        int getRustiness() { return rustiness; }
        void setRustiness(int runstiness) { this->rustiness = runstiness; }

        BasicDriver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes, int rustiness) : Driver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes), rustiness(rustiness) { };
        BasicDriver(ifstream& fin);

        void edit() override;

        void print() override;

        void save(ofstream& fout) override;
};
#endif