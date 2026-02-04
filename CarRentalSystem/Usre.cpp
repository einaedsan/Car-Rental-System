#include "User.h"

User::User() {
    isBlocked = false;
}

User::User(int Id, const string& n, const string& u, const string& pas) {

    id = Id;
    name = n;
    username = u;
    passwordHash = pas;
    isBlocked = false;
}

int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

string User::getUsername() const {
    return username;
}

bool User::blocked() const {
    return isBlocked;
}

void User::setBlocked(bool status) {
    isBlocked = status;
}

string User::getPasswordHash() const {
    return passwordHash;
}

