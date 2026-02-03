#include "User.h"

User::User() {
    isBlocked = false;
}

User::User(int id, string n, string u, string hash, UserRole r) {

    userId = id;
    name = n;
    username = u;
    passwordHash = hash;
    role = r;
    isBlocked = false;
}

int User::getUserId() const {
    return userId;
}

string User::getUsername() const {
    return username;
}

UserRole User::getRole() const {
    return role;
}

bool User::blocked() const {
    return isBlocked;
}

void User::setBlocked(bool status) {
    isBlocked = status;
}
