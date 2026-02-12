#include "AuthManager.h"
#include "PasswordHasher.h"
#include "Manager.h"
#include "Staff.h"
#include <iostream>

#include "UserStorage.h"
#include <conio.h>

using namespace std;
string getHiddenPassword() {
    string password;
    char ch;

    while (true) {
        ch = _getch();  // کاراکتر بدون نمایش گرفته میشه

        if (ch == 13) { // Enter
            break;
        }
        else if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  // پاک کردن ستاره
            }
        }
        else {
            password += ch;
            cout << "*";  // نمایش ستاره
        }
    }

    cout << endl;
    return password;
}

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
    password = getHiddenPassword();

    User* user = new User(
        users.generateNextId(),
        name,
        username,
        PasswordHasher::hash(password)
    );

    users.add(user);

    // 🔹 ذخیره روی CSV
    UserStorage::saveToCSV(users, "users.csv");

    cout << "✅ Registration successful\n";
}


User* AuthManager::login(UserList& users) {
    string username, password;

    cout << "Username: ";
    cin >> username;

    cout << "Password: ";
    password = getHiddenPassword();

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
    password = getHiddenPassword();

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
    password = getHiddenPassword();

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

