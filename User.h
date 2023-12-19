#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
    protected:
        int id;
        string name;
    public:
        int getId() { return id; }
        void setId(int newId) { id = newId; }

        string getName() { return name; }
        void setName(string newName) { name = newName; }

        bool operator == (User& otherUser) { return id == otherUser.getId(); }
};
#endif