#include "Rides.h"
#include "Ride.h"
#include <iostream>
#include <fstream>

using namespace std;

unsigned int Rides::getIndexOf(Ride* ride) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i] == ride) {
            return i;
        }
    }
    throw string("There is no index of that passenger");
}

void Rides::add(Ride* ride) {
    ride->setId(nextId);
    nextId++;
    rides.push_back(ride); 
}

void Rides::deleteRidesByStatus(rideStatus status) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getStatus() == status) {
            deleteARide(rides[i]);
        }
    }
}

Ride* Rides::searchById(int rideId) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getId() == rideId) {
            return rides[i];
        }
    }
    throw string("A ride by that id does not exist");
}

void Rides::printAll() {
    if(rides.size() == 0) cout << "No rides found.\n";
    for(unsigned int i = 0; i < rides.size(); i++) {
        rides[i]->print();
        cout << "\n";
    }
}

void Rides::printAll(rideStatus status) {
    bool anyFound = false;
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getStatus() == status) {
            rides[i]->print();
            anyFound = true;
            cout << "\n";
        }
    }
    if(!anyFound) cout << "No rides found with that status.\n";
}

void Rides::printAll(Driver* driver) {
    bool anyFound = false;
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getDriver() == driver) {
            rides[i]->print();
            anyFound = true;
            cout << "\n";
        }
    }
    if(!anyFound) cout << "No rides found with that driver.\n";
}

void Rides::printAll(Passenger* passenger) {
    bool anyFound = false;
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getPassenger() == passenger) {
            rides[i]->print();
            anyFound = true;
            cout << "\n";
        }
    }
    if(!anyFound) cout << "No rides found with that passenger.\n";
}

bool Rides::save(ofstream& fout) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        fout << "\n";
        rides[i]->save(fout);
    }
    return rides.size() > 0;
}

void Rides::readSave(ifstream& fin, Passengers* passengers, Drivers* drivers) {
    fin.ignore();
    while(!fin.eof()) {
        Ride* ride = new Ride(fin, passengers, drivers);
        rides.push_back(ride);
    }
    if(rides.size() != 0) nextId = rides[rides.size() - 1]->getId() + 1;
}

void Rides::deallocate() {
    for(unsigned int i = 0; i < rides.size(); i++) {
        delete rides[i];
    }
    rides.clear();
}

void Rides::deleteARide(Ride* ride) {
    rides.erase(rides.begin() + getIndexOf(ride));
    delete ride;
}

void Rides::deleteAllRidesInvolvingAPassenger(Passenger* passenger) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getPassenger() == passenger) {
            deleteARide(rides[i]);
        }
    }
}

void Rides::deleteAllRidesInvolvingADriver(Driver* driver) {
    for(unsigned int i = 0; i < rides.size(); i++) {
        if(rides[i]->getDriver() == driver) {
            deleteARide(rides[i]);
        }
    }
}