#include "User.h"

User::User() {
    id = 0;
    isBlocked = false;
    debt = 0;
    activeRentalsCount = 0;
}

User::User(int Id, const string& n, const string& u, const string& pas) {
    id = Id;
    name = n;
    username = u;
    passwordHash = pas;
    isBlocked = false;
    debt = 0;
    activeRentalsCount = 0;
}

User::User(const string& u, const string& pas) {
    id = 0;
    username = u;
    passwordHash = pas;
    isBlocked = false;
    debt = 0;
    activeRentalsCount = 0;
}

int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getUsername() const { return username; }
string User::getPasswordHash() const { return passwordHash; }

bool User::blocked() const { return isBlocked; }
void User::setBlocked(bool status) { isBlocked = status; }

double User::getDebt() const { return debt; }
int User::getActiveRentalsCount() const { return activeRentalsCount; }

void User::addDebt(double amount) { debt += amount; }

void User::payDebt(double amount) {
    debt -= amount;
    if (debt < 0) debt = 0;
}

void User::setDebt(double d) { debt = d; }
void User::setActiveRentalsCount(int c) { activeRentalsCount = c; }

void User::incrementActiveRentals() { activeRentalsCount++; }

void User::decrementActiveRentals() {
    if (activeRentalsCount > 0)
        activeRentalsCount--;
}

bool User::canRent() const {
    return !isBlocked &&
        activeRentalsCount < SystemConfig::MAX_ACTIVE_RENTALS &&
        debt <= SystemConfig::MAX_DEBT;
}
