#include "UserStorage.h"
#include <fstream>
#include <iostream>

using namespace std;

void UserStorage::saveToCSV(const UserList& users, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "❌ Cannot open file for writing\n";
        return;
    }

    file << "id,name,username,passwordHash,isBlocked,debt,activeRentals\n";

    UserNode* cur = users.getHead();
    while (cur != nullptr) {
        User* u = cur->data;

        file << u->getId() << ","
            << u->getName() << ","
            << u->getUsername() << ","
            << u->getPasswordHash() << ","
            << (u->blocked() ? "1" : "0") << ","
            << u->getDebt() << ","
            << u->getActiveRentalsCount()
            << "\n";

        cur = cur->next;
    }

    file.close();
    cout << "✅ Users saved to CSV\n";
}

void UserStorage::loadFromCSV(UserList& users, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "⚠️ CSV file not found, starting empty\n";
        return;
    }

    string line;
    getline(file, line); // skip header

    int maxId = 0;

    while (getline(file, line)) {
        int pos = 0;

        int comma = line.find(',', pos);
        int id = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        comma = line.find(',', pos);
        string name = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        string username = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        string hash = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        bool blocked = (line.substr(pos, comma - pos) == "1");
        pos = comma + 1;

        comma = line.find(',', pos);
        double debt = stod(line.substr(pos, comma - pos));
        pos = comma + 1;

        int activeRentals = stoi(line.substr(pos));

        User* u = new User(id, name, username, hash);
        u->setBlocked(blocked);
        u->setDebt(debt);
        u->setActiveRentalsCount(activeRentals);

        users.add(u);

        if (id > maxId)
            maxId = id;
    }

    users.syncLastId(maxId);

    file.close();
    cout << "✅ Users loaded from CSV\n";
}
