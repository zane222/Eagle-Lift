#ifndef GROUP_DRIVER_H
#define GROUP_DRIVER_H

#include <string>
#include "Driver.h"

using namespace std;

class GroupDriver : public Driver {
    public:
        GroupDriver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes) : Driver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes) { };
        GroupDriver(ifstream& fin) : Driver(fin) { }

        void edit() override;

        void print() override;

        void save(ofstream& fout) override;
};
#endif