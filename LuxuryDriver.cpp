#include <iostream>
#include <fstream>
#include "LuxuryDriver.h"
#include "InputHelper.h"

using namespace InputHelper;

LuxuryDriver::LuxuryDriver(ifstream& fin) : Driver(fin) {
    getline(fin, amenities);
}

void LuxuryDriver::print() {
    cout << "Vehicle class: Luxury\n";
    Driver::print();
    cout << "Amenities: " << amenities << "\n";
}

void LuxuryDriver::save(ofstream& fout) {
    fout << "luxury\n";
    Driver::save(fout);
    fout << "\n" << amenities;
}

void LuxuryDriver::edit() {
    cout << "User's current info:\n";
    print();
    cout << "Which value would you like to edit:\nn - name, c - vehicle's capacity for passengers, h - handicapped capable, t - type of vehicle, p - allow pets, w - notes, a - amenities (q - cancel edit):\n";
    char value;
    cin >> value;
    cin.ignore();
    if(value == 'n') {
        cout << "Enter your new name: ";
        string driverName;
        getline(cin, driverName);
        this->name = driverName;
    } else if(value == 'c') {
        cout << "Enter your vehicle's new capacity for passengers: ";
        int vehicleCapacity = getInt();
        while(vehicleCapacity < 1) {
            cout << "Invalid vehicle capacity, try again: ";
            vehicleCapacity = getInt();
        }
        this->vehicleCapacity = vehicleCapacity;
    } else if(value == 'h') {
        cout << "Is your vehicle handicapped capable now (y/n): ";
        this->handicappedCapable = getBool();
    } else if(value == 't') {
        cout << "Which type of vehicle do you have now (c - compact2Door, s - sedan4Door, S - SUV, v - Van, o - other):\n";
        char temp;
        cin >> temp;
        cin.ignore();
        while(!(temp == 'c' || temp == 's' || temp == 'S' || temp == 'v' || temp == 'o')) {
            cout << "Invalid vehicle type, try again: ";
            cin >> temp;
            cin.ignore();
        }
        this->vehicleType = (vehicle) temp;
    } else if(value == 'p') {
        cout << "Do you allow pets in your vehicle now: ";
        this->petsAllowed = getBool();
    } else if(value == 'w') {
        cout << "Write any notes you would like your passenger to know about you before you give them a ride (write 'n' if there are no notes): ";
        string notes;
        getline(cin, notes);
        this->notes = notes;
    } else if(value == 'a') {
        cout << "List all the amenities your vehicle has: ";
        string amenities;
        getline(cin, amenities);
        this->amenities = amenities;
    } else if(value == 'q') {
        cout << "Canceled\n";
    } else { 
        cout << "Invalid option chosen, restart.";
        edit();
    }
}