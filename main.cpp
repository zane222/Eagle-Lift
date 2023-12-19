// Zane Mouakket, ZaneMouakket@my.unt.edu, this program manages passengers and drivers, it allows them to make an account, edit, their account, schedual a ride 
//and many other things they may want to do. This program also allows a government auditor to view all the data that is stored in the system
#include <iostream>
#include <fstream>
#include <functional>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include "Driver.h"
#include "EconomyDriver.h"
#include "BasicDriver.h"
#include "GroupDriver.h"
#include "LuxuryDriver.h"
#include "Drivers.h"
#include "Passenger.h"
#include "Passengers.h"
#include "Ride.h"
#include "Rides.h"
#include "InputHelper.h"
//TODO: let the user pick which class to get a ride from
using namespace std;
using namespace InputHelper;

Drivers drivers;
Passengers passengers;
Rides rides;

time_t currentTime; //store the current time in the program simulation

enum userManipulation { createUser = 'c', editUser = 'e', deleteUser = 'd', printUser = 'p', requestARideOrChangeAvailability = 'r' };

enum adminManipulation { searchForPassenger = 'p', printAllPassengers = 'P', searchForDriver = 'd', printAllDrivers = 'D', searchForRide = 'r', printAllRides = 'R', printAllRidesOfASpecificStatus = 's', printAllRidesForASpecificPassenger = 'l', printAllRidesForASpecificDriver = 'L', deleteAllCanceledRides = 'c' };

void executeOnDriverSelection(userManipulation);
void executeOnPassengerSelection(userManipulation);
void executeOnAdminSelection(adminManipulation);

void saveEverything() {  //if they want to reset completely, they can just delete the savedata files
    ofstream pFout("SaveDataPassengers.txt");
    ofstream dFout("SaveDataDrivers.txt");
    ofstream rFout("SaveDataRides.txt");
    bool pWroteData = passengers.save(pFout);
    bool dWroteData = drivers.save(dFout);
    bool rWroteData = rides.save(rFout);
    pFout.close();
    dFout.close();
    rFout.close();
    if(!(pWroteData || dWroteData || rWroteData)) return;
    cout << "Data has been saved to ";
    if(pWroteData) {
        cout << "SaveDataPassengers.txt";
    }
    if(dWroteData) {
        if(pWroteData) cout << ", ";
        cout << "SaveDataDrivers.txt";
    }
    if(rWroteData) {
        if(pWroteData || dWroteData) cout << ", ";
        cout << "SaveDataRides.txt";
    }
    cout << "\n";
}

void showMenuAndGetSelectionUntilUserQuits() {
    cout << "----------------------------------------------------------------------------------------------------\nMenu:\n";
    printf("%-50s %s", "dc - create a new driver user", "pc - create a new passenger user\n");
    printf("%-50s %s", "de - edit details about a driver user", "pe - edit details about a passenger user\n");
    printf("%-50s %s", "dd - delete a driver user and their rides", "pd - delete a passenger user and their rides\n");
    printf("%-50s %s", "dp - print a driver user's details", "pp - print a passenger user's details\n");
    printf("%-50s %s", "dr - change availability", "pr - request a ride\n");
    cout << "\n";
    
    printf("%-50s %s", "aD - print all drivers", "ad - search for a driver\n");
    printf("%-50s %s", "aP - print all passengers", "ap - search for a passenger\n");
    printf("%-50s %s", "aR - print all rides", "ar - search for a ride\n");
    printf("%-50s %s", "as - print all rides of a specific status", "al - print all rides for a specific passenger\n");
    printf("%-50s %s", "aL - print all rides for a specific driver", "ac - delete all canceled rides\n");
    cout << "\n";
    
    cout << "qq - quit\n";
    
    cout << "Choice: ";
    char choice[2]; //choice[0] is if they want to act as a passenger, driver, or admin user, choice[1] is what they want to do as that user
    bool scanWorked = scanf("%s", choice);
    cin.ignore();

    if(!scanWorked) {
        cout << "Invalid selection.\n";
        showMenuAndGetSelectionUntilUserQuits();
        return;
    }
    
    if(choice[0] == 'd') { 
        if(!(choice[1] == createUser || choice[1] == editUser || choice[1] == deleteUser || choice[1] == printUser || choice[1] == requestARideOrChangeAvailability)) {
            cout << "Invalid selection.\n";
            showMenuAndGetSelectionUntilUserQuits();
            return;
        }
        executeOnDriverSelection(static_cast<userManipulation>(choice[1]));
    } else if(choice[0] == 'p') {
        if(!(choice[1] == createUser || choice[1] == editUser || choice[1] == deleteUser || choice[1] == printUser || choice[1] == requestARideOrChangeAvailability)) {
            cout << "Invalid selection.\n";
            showMenuAndGetSelectionUntilUserQuits();
            return;
        }
        executeOnPassengerSelection(static_cast<userManipulation>(choice[1]));
    } else if(choice[0] == 'a') {
        if(!(choice[1] == searchForPassenger || choice[1] == printAllPassengers || choice[1] == searchForDriver || choice[1] == printAllDrivers || choice[1] == searchForRide || choice[1] == printAllRides || choice[1] == printAllRidesOfASpecificStatus || choice[1] == printAllRidesForASpecificPassenger || choice[1] == printAllRidesForASpecificDriver || choice[1] == deleteAllCanceledRides)) {
            cout << "Invalid selection.\n";
            showMenuAndGetSelectionUntilUserQuits();
            return;
        }
        executeOnAdminSelection(static_cast<adminManipulation>(choice[1]));
    } else if(choice[0] == 'q') {
        saveEverything(); // just incase the saving right after an action doesn't work
        //deallocate everything
        drivers.deallocate();
        passengers.deallocate();
        rides.deallocate();
        return;
    } else {
        cout << "Invalid selection.\n";
    }
    showMenuAndGetSelectionUntilUserQuits();
}

Driver* getANewDriverFromInput() {
    cout << "Enter your name: ";
    string driverName;
    getline(cin, driverName);

    cout << "Enter your class of vehicle (e - economy 1-2 passengers, b - basic 2-4 passengers, g - group 5-7 passengers, l - luxury): ";
    char vehicleClass;
    cin >> vehicleClass;
    cin.ignore();
    while(!(vehicleClass == 'e' || vehicleClass == 'b' || vehicleClass == 'g' || vehicleClass == 'l')) { //make sure they picked a valid option
        cout << "Invalid vehicle class, try again: ";
        cin >> vehicleClass;
        cin.ignore();    
    }

    int vehicleCapacity;
    if(vehicleClass == 'e') {
        cout << "Enter your vehicle's capacity for passengers (1-2): ";
        vehicleCapacity = getInt();
        while(vehicleCapacity < 1 || vehicleCapacity > 2) {
            cout << "Invalid vehicle capacity, try again: ";
            vehicleCapacity = getInt();
        }
    } else if(vehicleClass == 'b') {
        cout << "Enter your vehicle's capacity for passengers (2-4): ";
        vehicleCapacity = getInt();
        while(vehicleCapacity < 2 || vehicleCapacity > 4) {
            cout << "Invalid vehicle capacity, try again: ";
            vehicleCapacity = getInt();
        }
    } else if(vehicleClass == 'g') {
        cout << "Enter your vehicle's capacity for passengers (5-7): ";
        vehicleCapacity = getInt();
        while(vehicleCapacity < 5 || vehicleCapacity > 7) {
            cout << "Invalid vehicle capacity, try again: ";
            vehicleCapacity = getInt();
        }
    } else if(vehicleClass == 'l') {
        cout << "Enter your vehicle's capacity for passengers: ";
        vehicleCapacity = getInt();
        while(vehicleCapacity < 1) {
            cout << "Invalid vehicle capacity, try again: ";
            vehicleCapacity = getInt();
        }
    }

    cout << "Is your vehicle handicapped capable (y/n): ";
    bool handicappedCapable = getBool();

    cout << "Which type of vehicle do you have (c - compact2Door, s - sedan4Door, S - SUV, v - Van, o - other): ";
    char temp;
    cin >> temp;
    cin.ignore();
    while(!(temp == 'c' || temp == 's' || temp == 'S' || temp == 'v' || temp == 'o')) { //make sure they picked a valid option
        cout << "Invalid vehicle type, try again: ";
        cin >> temp;
        cin.ignore();    
    }
    vehicle vehicleType = static_cast<vehicle>(temp);

    cout << "Do you allow pets in your vehicle (y/n): ";
    bool petsAllowed = getBool();

    cout << "Write any notes you would like your passenger to know about you before you give them a ride (write 'n' if there are no notes): ";
    string notes;
    getline(cin, notes);

    if(vehicleClass == 'e') {
        cout << "Is your vehicle electric (y/n): ";
        bool isElectric = getBool();
        return new EconomyDriver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes, isElectric);
    } else if(vehicleClass == 'b') {
        cout << "How rusty is your vehicle (on a scale of 1-10): ";
        int rustiness = getInt();
        while(rustiness < 1 || rustiness > 10) {
            cout << "Invalid vehicle rustiness, try again (scale of 1-10): ";
            rustiness = getInt();
        }
        return new BasicDriver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes, rustiness);
    } else if(vehicleClass == 'g') {
        return new GroupDriver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes);
    } else if(vehicleClass == 'l') {
        cout << "List all the amenities your vehicle has: ";
        string amenities;
        getline(cin, amenities);
        return new LuxuryDriver(driverName, vehicleCapacity, handicappedCapable, vehicleType, petsAllowed, notes, amenities);
    } else {
        throw string("Error 11"); // this shouldn't happen because vehicleClass is already checked
        return nullptr;
    }
}

Passenger* getANewPassengerFromInput() {
    cout << "Enter your name: ";
    string name;
    getline(cin, name);

    cout << "What is your prefered payment method (c - cash, C - CreditCard, p - payPal, o - other): ";
    char temp;
    cin >> temp;
    cin.ignore();
    while(!(temp == 'c' || temp == 'C' || temp == 'p' || temp == 'o')) {
        cout << "Invalid payment method, try again: ";
        cin >> temp;
        cin.ignore();
    }
    payment paymentPreference = static_cast<payment>(temp);

    cout << "Do you require a handicapped capable vehicle (y/n): ";
    bool handicapped = getBool();

    cout << "What is the minimum rating you require a driver to have (0.1-5.0): ";
    float defaultRatingRequired = getFloat();
    while(defaultRatingRequired < .01 || defaultRatingRequired > 5.0) { //make sure rating is between 0.1 and 5.0, if not, make them put it again.
        cout << "Not within the range, try again: ";
        defaultRatingRequired = getFloat();
    }

    cout << "Do have pets (y/n): ";
    bool hasPets = getBool();

    return new Passenger(name, paymentPreference, handicapped, defaultRatingRequired, hasPets);
}

Ride* getANewRideFromInput(Passenger* passenger) {
    if(!drivers.areAnyAvailable(passenger->getDefaultRatingRequired(), passenger->getHandicapped())) throw string("There are no drivers currently available with your requirements at this time");

    cout << "Enter the class of vehicle you would like to request a ride from (e - economy 1-2 passengers, b - basic 2-4 passengers, g - group 5-7 passengers, l - luxury, a - any): ";
    char vehicleClass;
    cin >> vehicleClass;
    cin.ignore();
    while(!(vehicleClass == 'e' || vehicleClass == 'b' || vehicleClass == 'g' || vehicleClass == 'l' || vehicleClass == 'a')) { //make sure they picked a valid option
        cout << "Invalid vehicle class, try again: ";
        cin >> vehicleClass;
        cin.ignore();    
    }
    
    cout << "Enter the address of where you would like to go: ";
    string dropoffLocation;
    getline(cin, dropoffLocation);

    cout << "Enter the address of where you are currently: ";
    string pickupLocation;
    getline(cin, pickupLocation);

    cout << "How many people will be riding: ";
    int sizeOfParty = getInt();
    if(sizeOfParty < 1) {
        cout << "Invalid size of party, restart.\n";
        return getANewRideFromInput(passenger);
    }

    bool includesPets = false;
    if(passenger->getHasPets()) {
        cout << "Are you going to be bringing any pets (y/n): ";
        includesPets = getBool();
    }

    Driver* thisDriver;
    if(vehicleClass == 'e') {
        if(!drivers.areAnyAvailableEconomy(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets)) throw string("There are no drivers currently available with those requirements at this time");
        thisDriver = drivers.getFirstAvailableEconomy(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets);
    } else if(vehicleClass == 'b') {
        if(!drivers.areAnyAvailableBasic(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets)) throw string("There are no drivers currently available with those requirements at this time");
        thisDriver = drivers.getFirstAvailableBasic(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets);
    } else if(vehicleClass == 'g') {
        if(!drivers.areAnyAvailableGroup(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets)) throw string("There are no drivers currently available with those requirements at this time");
        thisDriver = drivers.getFirstAvailableGroup(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets);
    } else if(vehicleClass == 'l') {
        if(!drivers.areAnyAvailableLuxury(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets)) throw string("There are no drivers currently available with those requirements at this time");
        thisDriver = drivers.getFirstAvailableLuxury(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets);
    } else if(vehicleClass == 'a') {
        if(!drivers.areAnyAvailable(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets)) throw string("There are no drivers currently available with those requirements at this time");
        thisDriver = drivers.getFirstAvailable(passenger->getDefaultRatingRequired(), passenger->getHandicapped(), sizeOfParty, includesPets);
    } else {
        throw string("Error 20"); // this shouldn't happen because vehicleClass is already checked
    }

    int estimatedTimeUntilPickupMinutes = rand() % 21 + 5; //5-25 minutes
    int estimatedTimeOfRideMinutes = rand() % 21 + 5; //5-25 minutes
    cout << "The nearest driver is " << estimatedTimeUntilPickupMinutes << " min away, is driving a " << thisDriver->getVehicleTypeString() << ", and has a rating of " << thisDriver->getDriverRating() << ". Once they pick you up, it will take " << estimatedTimeOfRideMinutes << " min to get you to your destination. Total time until arrival is " << (estimatedTimeUntilPickupMinutes + estimatedTimeOfRideMinutes) << " min.\n";
    if(thisDriver->getNotes() != "n") cout << "Here are some things the driver would like you to know: " << thisDriver->getNotes() << "\n";
    if(dynamic_cast<BasicDriver*>(thisDriver) != nullptr) cout << "The vehicle has a rustiness of " << dynamic_cast<BasicDriver*>(thisDriver)->getRustiness() << " on a scale of 1-10\n";
    if(dynamic_cast<EconomyDriver*>(thisDriver) != nullptr) cout << "The vehicle is " << (dynamic_cast<EconomyDriver*>(thisDriver)->getIsElectric() ? "" : "not ") << "electric\n";
    if(dynamic_cast<LuxuryDriver*>(thisDriver) != nullptr) cout << "Here are the vehicle's amenities: " << dynamic_cast<LuxuryDriver*>(thisDriver)->getAmenities() << "\n";
    cout << "Accept driver? (y/n): ";
    char temp;
    cin >> temp;
    cin.ignore();
    if(temp != 'y') throw string("The ride has aborted");
    //ride never gets created until the passenger accepts it
    return new Ride(passenger, thisDriver, currentTime, estimatedTimeUntilPickupMinutes, estimatedTimeOfRideMinutes, pickupLocation, dropoffLocation, sizeOfParty, includesPets);
}

void getNameOrIdThenDoSomethingAfter(function<void(string)> callbackForName, function<void(int)> callbackForId) { 
    cout << "Enter the name of the user (type 'i' if you would like to select by id): ";
    string name;
    getline(cin, name);
    if(name != "i") {
        callbackForName(name);
    } else {
        cout << "Enter the id of the user: ";
        callbackForId(getInt());
    }
}

void executeOnPassengerSelection(userManipulation manipulation) {
    try {
        if(manipulation == createUser) {
            passengers.add(getANewPassengerFromInput());
            cout << "User has been created.\n";
        } else if(manipulation == editUser) {
            getNameOrIdThenDoSomethingAfter([](string name) { //this function makes it so I don't have to write out 'passengers.edit(name);' twice, or have to write out the input prompt over and over
                passengers.edit(name);
            }, [](int id) {
                passengers.edit(id);
            });
            cout << "User has been edited.\n";
        } else if(manipulation == deleteUser) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                rides.deleteAllRidesInvolvingAPassenger(passengers.searchByName(name));
                passengers.remove(name);
            }, [](int id) {
                rides.deleteAllRidesInvolvingAPassenger(passengers.searchById(id));
                passengers.remove(id);
            });
            cout << "User has been deleted.\n";
        } else if(manipulation == printUser) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                passengers.print(name);
            }, [](int id) {
                passengers.print(id);
            });
        } else if(manipulation == requestARideOrChangeAvailability) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                Ride* ride = getANewRideFromInput(passengers.searchByName(name));
                rides.add(ride);
                currentTime = ride->getDropoffTime();
            }, [](int id) {
                Ride* ride = getANewRideFromInput(passengers.searchById(id));
                rides.add(ride);
                currentTime = ride->getDropoffTime();
            });
        } else {
            throw string("Error 4"); //the selection is already verified, so this line should never be ran
        }
    } catch(string error) {
        cout << error << ".\n";
    } catch(...) {
        cout << "Error, going back to main menu.\n";
    }
    saveEverything();
}

void executeOnDriverSelection(userManipulation manipulation) {
    try {
        if(manipulation == createUser) {
            drivers.add(getANewDriverFromInput());
            cout << "User has been created.\n";
        } else if(manipulation == editUser) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                drivers.edit(name);
            }, [](int id) {
                drivers.edit(id);
            });
            cout << "User has been edited.\n";
        } else if(manipulation == deleteUser) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                rides.deleteAllRidesInvolvingADriver(drivers.searchByName(name));
                drivers.remove(name);
            }, [](int id) {
                rides.deleteAllRidesInvolvingADriver(drivers.searchById(id));
                drivers.remove(id);
            });
            cout << "User has been deleted.\n";
        } else if(manipulation == printUser) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                drivers.print(name);
            }, [](int id) {
                drivers.print(id);
            });
        } else if(manipulation == requestARideOrChangeAvailability) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                drivers.changeAvailability(name);
            }, [](int id) {
                drivers.changeAvailability(id);
            });
        } else {
            throw string("Error 3"); //the selection is already verified, so this line should never be ran
        }
    } catch(string error) {
        cout << error << ".\n";
    } catch(...) {
        cout << "Error, going back to main menu.\n";
    }
    saveEverything();
}

void executeOnAdminSelection(adminManipulation manipulation) {
    try {
        if(manipulation == searchForPassenger) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                passengers.print(name);
            }, [](int id) {
                passengers.print(id);
            });
        } else if(manipulation == printAllPassengers) {
            passengers.printAll();
        } else if(manipulation == searchForDriver) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                drivers.print(name);
            }, [](int id) {
                drivers.print(id);
            });
        } else if(manipulation == printAllDrivers) {
            drivers.printAll();
        } else if(manipulation == searchForRide) {
            cout << "Enter the id: ";
            rides.print(getInt());
        } else if(manipulation == printAllRides) {
            rides.printAll();
        } else if(manipulation == printAllRidesOfASpecificStatus) {
            cout << "Pick the status to print (a - active, c - completed, C - Cancelled): ";
            char temp;
            cin >> temp;
            if(!(temp == active || temp == completed || temp == Cancelled)) {
                cout << "Invalid selection.\n";
                executeOnAdminSelection(manipulation);
                return;
            }
            rides.printAll(static_cast<rideStatus>(temp));
        } else if(manipulation == printAllRidesForASpecificPassenger) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                Passenger* passenger;
                passenger = passengers.searchByName(name);
                rides.printAll(passenger);
            }, [](int id) {
                Passenger* passenger;
                passenger = passengers.searchById(id);
                rides.printAll(passenger);
            });
        } else if(manipulation == printAllRidesForASpecificDriver) {
            getNameOrIdThenDoSomethingAfter([](string name) {
                Driver* driver;
                driver = drivers.searchByName(name);
                rides.printAll(driver);
            }, [](int id) {
                Driver* driver;
                driver = drivers.searchById(id);
                rides.printAll(driver);
            });
        } else if(manipulation == deleteAllCanceledRides) {
            rides.deleteRidesByStatus(Cancelled);
            cout << "All canceled rides have been deleted.\n";
        } else {
            throw string("Error 2"); //the selection is already verified, so this line should never be ran
        }
    } catch(string error) {
        cout << error << ".\n";
    } catch(...) {
        cout << "Error, going back to main menu.\n";
    }
    saveEverything();
}

bool doesFileHaveAnyData(ifstream& fin) {
    if(!fin.is_open()) return false;
    return fin.peek() != std::ifstream::traits_type::eof();
}

void readPreviousSave() {
    ifstream pFin("SaveDataPassengers.txt");
    ifstream dFin("SaveDataDrivers.txt");
    ifstream rFin("SaveDataRides.txt");
    bool pHasData = doesFileHaveAnyData(pFin);
    bool dHasData = doesFileHaveAnyData(dFin);
    bool rHasData = doesFileHaveAnyData(rFin);
    if(!(pHasData || dHasData || rHasData)) return; //Just return, there doesn't need to be an error if it doesn't work because it could their first time using the program
    cout << "Data has been read from ";
    if(pHasData) { //only output the ones that get opened onto the screen as being read
        passengers.readSave(pFin);
        cout << "SaveDataPassengers.txt";
    }
    if(dHasData) {
        drivers.readSave(dFin);
        if(pHasData) cout << ", ";
        cout << "SaveDataDrivers.txt";
    }
    if(rHasData) {
        rides.readSave(rFin, &passengers, &drivers);
        if(pHasData || dHasData) cout << ", ";
        cout << "SaveDataRides.txt";
    }
    cout << "\n";
    pFin.close();
    dFin.close();
    rFin.close();
}

int main() {
    cout << "Homework 4, Zane Mouakket, ZaneMouakket@my.unt.edu, CSCE 1040.002\n";
    cout << "Whenever you want to start again from the begining, exit the program and type 'rm *.txt'\n";
    srand(time(NULL)); //set the seed
    currentTime = time(NULL);
    readPreviousSave();
    showMenuAndGetSelectionUntilUserQuits();
    return 0;
}