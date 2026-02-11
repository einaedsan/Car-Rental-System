#include "FleetStorage.h"
#include <fstream>
#include <iostream>

using namespace std;

void FleetStorage::saveCars(const Fleet& fleet, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "? Cannot open cars file for writing\n";
        return;
    }

    file << "id,plate,brand,model,type,price,status\n";

    CarNode* cur = fleet.getCarList().getHead();
    while (cur != NULL) {
        Car* c = cur->data;
        file << c->getId() << ","
            << c->getPlate() << ","
            << c->getBrand() << ","
            << c->getModel() << ","
            << c->getType() << ","
            << c->getPricePerDay() << ","
            << c->getStatus() << "\n";
        cur = cur->next;
    }

    file.close();
}

void FleetStorage::loadCars(Fleet& fleet, const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cout << "? Cannot open cars file for reading\n";
        return;
    }

    int maxId = 0;
    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        string plate, brand, model, type;
        double price;
        int id, status;

        int pos = 0;
        int prev = 0;

        id = stoi(line.substr(prev, (pos = line.find(',', prev)) - prev));
        prev = pos + 1;

        plate = line.substr(prev, (pos = line.find(',', prev)) - prev);
        prev = pos + 1;

        brand = line.substr(prev, (pos = line.find(',', prev)) - prev);
        prev = pos + 1;

        model = line.substr(prev, (pos = line.find(',', prev)) - prev);
        prev = pos + 1;

        type = line.substr(prev, (pos = line.find(',', prev)) - prev);
        prev = pos + 1;

        price = stod(line.substr(prev, (pos = line.find(',', prev)) - prev));
        prev = pos + 1;

        status = stoi(line.substr(prev));

        if (id > maxId)
            maxId = id;

        Car* car = new Car(
            id,
            plate,
            brand,
            model,
            type,
            price,
            (CarStatus)status
        );

        fleet.addCar(car);
    }

    Car::syncNextId(maxId);
    file.close();
}
