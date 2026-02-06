#include "MaintenanceStorage.h"
#include <fstream>
#include <iostream>

using namespace std;

void MaintenanceStorage::save(const MaintenanceList& list, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "❌ Cannot open maintenance file for writing\n";
        return;
    }

    file << "id,carId,day,description,cost\n";

    MaintenanceNode* cur = list.getHead();
    while (cur != NULL) {
        Maintenance* m = cur->data;
        file << m->getId() << ","
            << m->getCarId() << ","
            << m->getDay() << ","
            << m->getDescription() << ","
            << m->getCost() << "\n";
        cur = cur->next;
    }

    file.close();
}

void MaintenanceStorage::load(MaintenanceList& list, const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "❌ Cannot open maintenance file for reading\n";
        return;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        int carId, day;
        double cost;
        string description;

        int pos = 0;
        int prev = 0;

        // skip maintenanceId
        prev = line.find(',') + 1;

        // carId
        carId = stoi(line.substr(prev, (pos = line.find(',', prev)) - prev));
        prev = pos + 1;

        // day
        day = stoi(line.substr(prev, (pos = line.find(',', prev)) - prev));
        prev = pos + 1;

        // description
        description = line.substr(prev, (pos = line.find(',', prev)) - prev);
        prev = pos + 1;

        // cost
        cost = stod(line.substr(prev));

        Maintenance* m = new Maintenance(day, carId, description, cost);
        list.addMaintenance(m);
    }

    file.close();
}

