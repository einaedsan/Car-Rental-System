#include "AuthManager.h"
#include "PasswordHasher.h"
#include "Manager.h"
#include "Staff.h"
#include <iostream>

using namespace std;

void AuthManager::signUp(UserList& users) {
    string name, username, password;

    cout << "Name: ";
    cin >> name;

    cout << "Username: ";
    cin >> username;

    if (users.findByUsername(username) != nullptr) {
        cout << "❌ Username already exists\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    User* user = new User(
        users.generateNextId(),
        name,
        username,
        PasswordHasher::hash(password)
    );

    users.add(user);
    cout << "✅ Registration successful\n";
}

User* AuthManager::login(UserList& users) {
    string username, password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    User* user = users.findByUsername(username);
    if (!user) {
        cout << "❌ User not found\n";
        return nullptr;
    }

    if (user->getPasswordHash() == PasswordHasher::hash(password)) {

        if (user->blocked()) {
            cout << "⛔ User is blocked\n";
            return nullptr;
        }

        cout << "✅ Login successful\n";
        return user;
    }

    cout << "❌ Wrong password\n";
    return nullptr;
}

bool AuthManager::loginManager() {
    string username, password;

    cout << "Manager username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    Manager* manager = Manager::getInstance();

    if (username != manager->getUsername()) {
        cout << "❌ Invalid manager username\n";
        return false;
    }

    if (password != manager->getPasswordHash()) {
        cout << "❌ Wrong password\n";
        return false;
    }

    cout << "✅ Manager login successful\n";
    return true;
}

bool AuthManager::loginStaff() {
    string username, password;

    cout << "Staff username: ";
    cin >> username;

    cout << "Password: ";
    cin >> password;

    Staff* staff = Staff::getInstance();

    if (username != staff->getUsername()) {
        cout << "❌ Invalid staff username\n";
        return false;
    }

    if (password != staff->getPasswordHash()) {
        cout << "❌ Wrong password\n";
        return false;
    }

    cout << "✅ Staff login successful\n";
    return true;
}

