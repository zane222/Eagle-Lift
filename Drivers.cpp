#include <iostream>
#include <fstream>
#include "Driver.h"
#include "EconomyDriver.h"
#include "BasicDriver.h"
#include "GroupDriver.h"
#include "LuxuryDriver.h"
#include "Drivers.h"

unsigned int Drivers::getIndexOf(Driver* driver) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i] == driver) {
            return i;
        }
    }
    throw string("That driver does not exist");
}

void Drivers::add(Driver* driver) {// id won't be assigned until the driver is put into drivers
    driver->setId(nextId);
    nextId++;
    drivers.push_back(driver); 
}

Driver* Drivers::searchByName(string name) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getName() == name) {
            return drivers[i];
        }
    }
    throw string("A driver by that name does not exist");
}

void Drivers::remove(Driver* driver) {
    drivers.erase(drivers.begin() + getIndexOf(driver));
    delete driver;
}

Driver* Drivers::searchById(int id) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getId() == id) {
            return drivers[i];
        }
    }
    throw string("A driver by that id does not exist");
}

void Drivers::printAll() { 
    if(drivers.size() == 0) cout << "No drivers found.\n";
    for(unsigned int i = 0; i < drivers.size(); i++) {
        drivers[i]->print();
        cout << "\n";
    }
}

Driver* Drivers::getFirstAvailable() {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable()) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailable(int defaultRatingRequired, bool handicapped) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped)) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailableEconomy(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<EconomyDriver*>(drivers[i]) != nullptr) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailableBasic(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<BasicDriver*>(drivers[i]) != nullptr) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailableGroup(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<GroupDriver*>(drivers[i]) != nullptr) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailableLuxury(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<LuxuryDriver*>(drivers[i]) != nullptr) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

Driver* Drivers::getFirstAvailable(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets)) {
            return drivers[i];
        }
    }
    throw string("There are no drivers currently available");
}

bool Drivers::areAnyAvailable() {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable()) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailable(int defaultRatingRequired, bool handicapped) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped)) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailableEconomy(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<EconomyDriver*>(drivers[i]) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailableBasic(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<BasicDriver*>(drivers[i]) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailableGroup(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<GroupDriver*>(drivers[i]) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailableLuxury(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets) && dynamic_cast<LuxuryDriver*>(drivers[i]) != nullptr) {
            return true;
        }
    }
    return false;
}

bool Drivers::areAnyAvailable(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        if(drivers[i]->getAvailable() && drivers[i]->getDriverRating() >= defaultRatingRequired && (drivers[i]->getHandicappedCapable() || !handicapped) && drivers[i]->getVehicleCapacity() >= sizeOfParty && (drivers[i]->getPetsAllowed() || !includesPets)) {
            return true;
        }
    }
    return false;
}

bool Drivers::save(ofstream& fout) {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        fout << "\n";
        drivers[i]->save(fout);
    }
    return drivers.size() > 0;
}

void Drivers::readSave(ifstream& fin) {
    fin.ignore();
    while(!fin.eof()) {
        string temp;
        getline(fin, temp);
        if(temp == "economy") {
            EconomyDriver* economyDriver = new EconomyDriver(fin);
            drivers.push_back(economyDriver);
        } else if(temp == "basic") {
            BasicDriver* basicDriver = new BasicDriver(fin);
            drivers.push_back(basicDriver);
        } else if(temp == "group") {
            GroupDriver* groupDriver = new GroupDriver(fin);
            drivers.push_back(groupDriver);
        } else if(temp == "luxury") {
            LuxuryDriver* luxuryDriver = new LuxuryDriver(fin);
            drivers.push_back(luxuryDriver);
        }
    }
    if(drivers.size() != 0) nextId = drivers[drivers.size() - 1]->getId() + 1;
}

void Drivers::deallocate() {
    for(unsigned int i = 0; i < drivers.size(); i++) {
        delete drivers[i];
    }
    drivers.clear();
}