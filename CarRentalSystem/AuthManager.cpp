#include "AuthManager.h"
#include "PasswordHasher.h"
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
