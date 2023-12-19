#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include "User.h"

using namespace std;

enum vehicle { compact2Door = 'c', sedan4Door = 's', SUV = 'S', van = 'v', Other = 'o' };

class Driver : public User {
    protected:
        int vehicleCapacity;
        bool handicappedCapable;
        vehicle vehicleType;
        float driverRating = 5.0; //rating will always start off at 5.0
        bool available = true;
        bool petsAllowed;
        string notes;

        string convertVehicleTypeToString(vehicle vehicleType);
    public:
        int getVehicleCapacity() { return vehicleCapacity; }
        void setVehicleCapacity(int newVehicleCapacity) { vehicleCapacity = newVehicleCapacity; }
        
        bool getHandicappedCapable() { return handicappedCapable; }
        void setHandicappedCapable(bool newHandicappedCapable) { handicappedCapable = newHandicappedCapable; }
        
        vehicle getVehicleType() { return vehicleType; }
        void setVehicleType(vehicle newVehicleType) { vehicleType = newVehicleType; }
        string getVehicleTypeString() { return convertVehicleTypeToString(vehicleType); }

        float getDriverRating() { return driverRating; }
        void setDriverRating(float newDriverRating) { driverRating = newDriverRating; }
        
        bool getAvailable() { return available; }
        void setAvailable(bool newAvailable) { available = newAvailable; }
        
        bool getPetsAllowed() { return petsAllowed; }
        void setPetsAllowed(bool newPetsAllowed) { petsAllowed = newPetsAllowed; }
        
        string getNotes() { return notes; }
        void setNotes(string newNotes) { notes = newNotes; }
    
        Driver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes);
        Driver(ifstream& fin);
    
        virtual void print();
    
        virtual void edit() = 0; // make this a pure virtual function
    
        void changeAvailability();

        virtual void save(ofstream& fout);

        virtual ~Driver() { }
};
#endif