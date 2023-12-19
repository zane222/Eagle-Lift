#include <iostream>
#include <fstream>
#include <iomanip>
#include "Passenger.h"
#include "InputHelper.h"

using namespace InputHelper;

Passenger::Passenger(string name, payment paymentPreference, bool handicapped, float defaultRatingRequired, bool hasPets) {
    this->name = name;
    this->paymentPreference = paymentPreference;
    this->handicapped = handicapped;
    this->defaultRatingRequired = defaultRatingRequired;
    this->hasPets = hasPets;
}

Passenger::Passenger(ifstream& fin) {
    getline(fin, name);
    fin >> id;
    fin.ignore();
    char temp;
    fin >> temp;
    fin.ignore();
    paymentPreference = (payment) temp;
    fin >> handicapped;
    fin.ignore();
    fin >> defaultRatingRequired;
    fin.ignore();
    fin >> hasPets;
    fin.ignore();
}

string convertPaymentTypeToString(payment paymentType) {
    if(paymentType == cash) {
        return "Cash";
    } else if(paymentType == CreditCard) {
        return "Credit card";
    } else if(paymentType == payPal) {
        return "PayPal";
    } else if(paymentType == other) {
        return "Other";
    } else {
        throw string("Error 6"); //the selection is already verified, so this line should never be ran
    }
}

void Passenger::print() {
    cout << "Name: " << name << "\nId: " << id << "\nPayment preference: " << convertPaymentTypeToString(paymentPreference) << "\nHandicapped: " << (handicapped ? "yes" : "no") << "\nRequired driver rating: " << fixed << setprecision(2) << defaultRatingRequired << "\nHas pets: " << (hasPets ? "yes" : "no") << "\n";
}

void Passenger::edit() {
    cout << "User's current info:\n";
    print();
    cout << "Which value would you like to edit:\nn - name, p - prefered payment method, h - handicapped, m - minimum driver rating required, H - Has pets:\n";
    char value;
    cin >> value;
    cin.ignore();
    if(value == 'n') {
        cout << "Enter your new name: ";
        string name;
        getline(cin, name);
        this->name = name;
    } else if(value == 'p') {
        cout << "Enter new prefered payment method (c - cash, C - CreditCard, p - payPal, o - other):\n";
        char temp;
        cin >> temp;
        cin.ignore();
        while(!(temp == 'c' || temp == 'C' || temp == 'p' || temp == 'o')) {
            cout << "Invalid payment method, try again: ";
            cin >> temp;
            cin.ignore();
        }
        this->paymentPreference = (payment) temp;
    } else if(value == 'h') {
        cout << "Do you require a handicapped capable vehicle now (y/n): ";
        this->handicapped = getBool();
    } else if(value == 'm') {
        cout << "What is the new minimum rating you require a driver to have (0.1-5.0): ";
        float defaultRatingRequired = getFloat();
        while(defaultRatingRequired < .01 || defaultRatingRequired > 5.0) {
            cout << "Not within the range, try again: ";
            defaultRatingRequired = getFloat();
        }
        this->defaultRatingRequired = defaultRatingRequired;
    } else if(value == 'H') {
        cout << "Do have pets now (y/n): ";
        this->hasPets = getBool();
    } else {
        cout << "Invalid option, restart.\n";
        edit();
        return;
    }
}

void Passenger::save(ofstream& fout) {
    fout << name << "\n" << id << "\n" << (char) paymentPreference << "\n" << handicapped << "\n" << defaultRatingRequired << "\n" << hasPets;
}