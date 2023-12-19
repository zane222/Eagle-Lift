#include "Passenger.h"
#include "Passengers.h"
#include <iostream>
#include <fstream>
#include <cassert>

unsigned int Passengers::getIndexOf(Passenger* passenger) {
    for(unsigned int i = 0; i < passengers.size(); i++) {
        if(passengers[i] == passenger) {
            return i;
        }
    }
    throw string("There is no index of that passenger");
}

void Passengers::add(Passenger* passenger) {
    passenger->setId(nextId);
    nextId++;
    passengers.push_back(passenger); 
}

Passenger* Passengers::searchByName(string name) {
    for(unsigned int i = 0; i < passengers.size(); i++) {
        if(passengers[i]->getName() == name) {
            return passengers[i];
        }
    }
    throw string("A passenger by that name does not exist");
}

Passenger* Passengers::searchById(int id) {
    for(unsigned int i = 0; i < passengers.size(); i++) {
        if(passengers[i]->getId() == id) {
            return passengers[i];
        }
    }
    throw string("A passenger by that id does not exist");
}

void Passengers::printAll() { 
    if(passengers.size() == 0) cout << "No passengers found.\n";
    for(unsigned int i = 0; i < passengers.size(); i++) {
        passengers[i]->print();
        cout << "\n";
    }
}

bool Passengers::save(ofstream& fout) {
    for(unsigned int i = 0; i < passengers.size(); i++) {
        fout << "\n";
        passengers[i]->save(fout);
    }
    return passengers.size() > 0;
}

void Passengers::readSave(ifstream& fin) {
    fin.ignore();
    while(!fin.eof()) {
        Passenger* passenger = new Passenger(fin);
        passengers.push_back(passenger);
    }
    if(passengers.size() != 0) nextId = passengers[passengers.size() - 1]->getId() + 1;
}

void Passengers::deallocate() {
    for(unsigned int i = 0; i < passengers.size(); i++) {
        delete passengers[i];
    }
    passengers.clear();
}

void Passengers::remove(Passenger* passenger) {
    passengers.erase(passengers.begin() + getIndexOf(passenger));
    delete passenger;
}