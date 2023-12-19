#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <stdio.h>
#include "Passenger.h"
#include "Passengers.h"
#include "Driver.h"
#include "Drivers.h"
#include "Ride.h"
#include "InputHelper.h"

using namespace std;
using namespace InputHelper;

Ride::Ride(Passenger* passenger, Driver* driver, time_t rideCreationTime, int estimatedTimeUntilPickupMinutes, int estimatedTimeOfRideMinutes, string pickupLocation, string dropoffLocation, int sizeOfParty, bool includesPets) {
    this->driver = driver;
    this->passenger = passenger;
    this->pickupLocation = pickupLocation;
    this->dropoffLocation = dropoffLocation;
    this->sizeOfParty = sizeOfParty;
    this->includesPets = includesPets;

    this->status = active;
    driver->setAvailable(false);
    cout << "The driver is on their way (type s to skip waiting, or c to cancel): ";
    char temp;
    cin >> temp;
    cin.ignore();
    if(temp == 'c') {
        driver->setAvailable(true);
        this->status = Cancelled;
        this->ratingByCustomer = 5;
        this->pickupTime = rideCreationTime;
        this->dropoffTime = rideCreationTime;
        return;
    }
    
    srand(time(NULL)); //seed the randomizer
    //actual time until pickup won't be the same as estimated ride time
    int actualTimeUntilPickupMinutes = estimatedTimeUntilPickupMinutes + (rand() % 9 - 4);
    this->pickupTime = rideCreationTime + (actualTimeUntilPickupMinutes * 60);

    int actualTimeOfRideMinutes = estimatedTimeOfRideMinutes + (rand() % 9 - 4); //actual ride time won't be the same as estimated ride time
    this->dropoffTime = pickupTime + (actualTimeOfRideMinutes * 60);
    cout << "You have arrived at your destination. It took " << actualTimeUntilPickupMinutes << " min + " << actualTimeOfRideMinutes << " min = " << (actualTimeUntilPickupMinutes + actualTimeOfRideMinutes) << " min. Leave a rating (0.1-5.0): ";
    float ratingByCustomer = getFloat();
    while(ratingByCustomer > 5 || ratingByCustomer < .1) {
        cout << "Invalid rating. Enter a rating within the range of 0.1-5.0: ";
        ratingByCustomer = getFloat();
    }

    this->ratingByCustomer = ratingByCustomer;
    driver->setDriverRating((ratingByCustomer + (2 * driver->getDriverRating())) / 3);

    //ride is finished
    this->status = completed;
    driver->setAvailable(true);
}

Ride::Ride(ifstream& fin, Passengers* passengers, Drivers* drivers) {
    fin >> id;
    fin.ignore();
    getline(fin, pickupLocation);
    fin >> pickupTime;
    fin.ignore();
    getline(fin, dropoffLocation);
    fin >> sizeOfParty;
    fin.ignore();
    fin >> includesPets;
    fin.ignore();
    fin >> dropoffTime;
    fin.ignore();
    char temp;
    fin >> temp;
    fin.ignore();
    status = (rideStatus) temp;
    fin >> ratingByCustomer;
    fin.ignore();
    try {
        int passengerId;
        fin >> passengerId;
        fin.ignore();
        passenger = passengers->searchById(passengerId);
        int driverId;
        fin >> driverId;
        fin.ignore();
        driver = drivers->searchById(driverId);
    } catch(string) {
        cout << "\nError, you may have deleted or moved a passengers or drivers SaveData file, but kept the rides SaveData file. Fix this by moving the passengers or drivers SaveData file back where it was, or delete all SaveData files\n";
    }
}

string Ride::convertStatusToString(rideStatus status) {
    if(status == active) {
        return "Active";
    } else if(status == completed) {
        return "Completed";
    } else if(status == Cancelled) {
        return "Cancelled";
    } else {
        throw string("Error 1"); //the selection is already verified, so this line should never be ran
    }
}

string formatTime(time_t time) { //format the time myself so that there won't be a bunch of extra stuff like seconds and day of the week if I just used ctime() 
    struct tm* timeinfo = localtime(&time);
    
    char formatted_string[100];
    sprintf(formatted_string, "%i/%i %i:%02i", timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min); //format ex. 10/22 16:06

    return formatted_string;
}

void Ride::print() {
    cout << "ID: " << id << "\nLocation: " << pickupLocation << " -> " << dropoffLocation << "\nTime: " << formatTime(pickupTime) << " -> " << formatTime(dropoffTime) << "\nSize of party: " << sizeOfParty << "\nIncludes pets: " << (includesPets ? "yes" : "no") << "\nStatus: " << convertStatusToString(status) << "\nCustomer rating: " << fixed << setprecision(1) << ratingByCustomer << "/5.0\nPassenger: " << passenger->getName() << " (ID: " << passenger->getId() << ")\nDriver: " << driver->getName() << " (ID: " << driver->getId() << ")\n";
}

void Ride::save(ofstream& fout) {
    fout << id << "\n" << pickupLocation << "\n" << pickupTime << "\n" << dropoffLocation << "\n" << sizeOfParty << "\n" << includesPets << "\n" << dropoffTime << "\n" << (char) status << "\n" << ratingByCustomer << "\n" << passenger->getId() << "\n" << driver->getId();
}
/* don't do this because the objects are already deletes by the passengers and drivers collections becuase they point to the same thing
Ride::~Ride() {
    delete passenger;
    delete driver;
}
*/