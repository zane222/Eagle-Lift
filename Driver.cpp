#include <iostream>
#include <fstream>
#include <iomanip>
#include "Driver.h"
#include "InputHelper.h"

using namespace InputHelper;

Driver::Driver(string driverName, int vehicleCapacity, bool handicappedCapable, vehicle vehicleType, bool petsAllowed, string notes) {
    this->name = driverName;
    this->vehicleCapacity = vehicleCapacity;
    this->handicappedCapable = handicappedCapable;
    this->vehicleType = vehicleType;
    this->petsAllowed = petsAllowed;
    this->notes = notes;
}

Driver::Driver(ifstream& fin) {
    fin >> id;
    fin.ignore();
    getline(fin, name);
    fin >> vehicleCapacity;
    fin.ignore();
    fin >> handicappedCapable;
    fin.ignore();
    char temp;
    fin >> temp;
    fin.ignore();
    vehicleType = (vehicle) temp;
    fin >> driverRating;
    fin.ignore();
    fin >> available;
    fin.ignore();
    fin >> petsAllowed;
    fin.ignore();
    getline(fin, notes);
}

string Driver::convertVehicleTypeToString(vehicle vehicleType) {
    if(vehicleType == compact2Door) {
        return "Compact 2 door";
    } else if(vehicleType == sedan4Door) {
        return "Sedan 4 door";
    } else if(vehicleType == SUV) {
        return "SUV";
    } else if(vehicleType == van) {
        return "Van";
    } else if(vehicleType == Other) {
        return "Other";
    } else {
        throw string("Error 5"); //the selection is already verified, so this line should never be ran
    }
}

void Driver::print() {
    cout << "Name: " << name << "\nId: " << id << "\nVehicle capacity: " << vehicleCapacity << "\nHandicapped capable: " << (handicappedCapable ? "yes" : "no") << "\nVehicle type: " << convertVehicleTypeToString(vehicleType) << "\nDriver rating: " << fixed << setprecision(2) << driverRating << "\nAvailable: " << (available ? "yes" : "no") << "\nPets allowed: " << (petsAllowed ? "yes" : "no") << "\nNotes: " << notes << "\n";
}

void Driver::changeAvailability() { 
    available = !available;
    cout << "Availability changed to " << (available ? "" : "not ") << "available.\n";
}

void Driver::save(ofstream& fout) {
    fout << id << "\n" << name << "\n" << vehicleCapacity << "\n" << handicappedCapable << "\n" << (char) vehicleType << "\n" << driverRating << "\n" << available << "\n" << petsAllowed << "\n" << notes;
}