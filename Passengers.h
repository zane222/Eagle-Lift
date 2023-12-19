#ifndef PASSENGERS_H
#define PASSENGERS_H

#include <vector>
#include "Passenger.h"

class Passengers {
    private:
        vector<Passenger*> passengers;
        unsigned int getIndexOf(Passenger* passenger); //the user doesn't need to know the index of something, so this is private
        int nextId = 100001;
    public:
        void add(Passenger* passenger);

        void edit(Passenger* passenger) { passenger->edit(); }
        void edit(string name) { edit(searchByName(name)); }
        void edit(int id) { edit(searchById(id)); }

        void remove(Passenger* passenger);
        void remove(string name) { remove(searchByName(name)); }
        void remove(int id) { remove(searchById(id)); }

        Passenger* searchByName(string name);
        Passenger* searchById(int name);

        void print(Passenger* passenger) { passenger->print(); }
        void print(string name) { print(searchByName(name)); }
        void print(int id) { print(searchById(id)); }

        void printAll();

        bool save(ofstream& fout);
        void readSave(ifstream& fin);

        void deallocate();
};
#endif