#include <iostream>
#include "InputHelper.h"

using namespace std;

int InputHelper::getInt() {
    int temp;
    cin >> temp;
    cin.ignore();
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid, try again: ";
        return getInt();
    }
    return temp;
}

float InputHelper::getFloat() {
    float temp;
    cin >> temp;
    cin.ignore();
    if(cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid, try again: ";
        return getFloat();
    }
    return temp;
}

bool InputHelper::getBool() {
    char temp;
    cin >> temp;
    cin.ignore();
    if(temp != 'y' && temp != 'n') {
        cout << "Invalid, try again: ";
        return getBool();
    }
    return (temp == 'y');
}