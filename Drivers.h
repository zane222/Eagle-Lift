#ifndef DRIVERS_H
#define DRIVERS_H

#include <vector>
#include "Driver.h"

class Drivers {
    private:
        vector<Driver*> drivers;
        int nextId = 100001;
        
        unsigned int getIndexOf(Driver* driver);  //the user doesn't need to know the index of something, so this is private
    public:
        void add(Driver* driver);
        
        void edit(Driver* driver) { driver->edit(); }
        void edit(string name) { edit(searchByName(name)); }
        void edit(int id) { edit(searchById(id)); }
        
        void remove(Driver* driver);
        void remove(string name) { remove(searchByName(name)); }
        void remove(int id) { remove(searchById(id)); }

        Driver* searchByName(string name);
        Driver* searchById(int id);
        
        void print(Driver* driver) { driver->print(); }
        void print(string name) { print(searchByName(name)); }
        void print(int id) { print(searchById(id)); }
        
        void printAll();

        void changeAvailability(Driver* driver) { driver->changeAvailability(); }
        void changeAvailability(string name) { changeAvailability(searchByName(name)); }
        void changeAvailability(int id) { changeAvailability(searchById(id)); }

        bool areAnyAvailable();
        bool areAnyAvailable(int defaultRatingRequired, bool handicapped); // are any available with these requirements
        bool areAnyAvailableEconomy(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        bool areAnyAvailableBasic(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        bool areAnyAvailableGroup(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        bool areAnyAvailableLuxury(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        bool areAnyAvailable(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements

        Driver* getFirstAvailable();
        Driver* getFirstAvailable(int defaultRatingRequired, bool handicapped); // are any available with these requirements
        Driver* getFirstAvailableEconomy(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        Driver* getFirstAvailableBasic(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        Driver* getFirstAvailableGroup(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        Driver* getFirstAvailableLuxury(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements
        Driver* getFirstAvailable(int defaultRatingRequired, bool handicapped, int sizeOfParty, bool includesPets); // are any available with these requirements

        bool save(ofstream& fout);
        void readSave(ifstream& fin);

        void deallocate();
};
#endif