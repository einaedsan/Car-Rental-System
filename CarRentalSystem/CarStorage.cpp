#include "CarStorage.h"
#include <fstream>
#include <iostream>
#include "Car.h"  

using namespace std;

void CarStorage::saveToCSV(const CarList& cars, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "❌ Cannot open car file\n";
        return;
    }

    file << "id,plate,brand,model,type,price,status\n";

    CarNode* cur = cars.getHead();
    while (cur != nullptr) {
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
    cout << "✅ Cars saved to CSV\n";
}

void CarStorage::loadFromCSV(CarList& cars, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "⚠️ Car CSV not found, starting empty\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    int maxId = 0;

    while (getline(file, line)) {
        int pos = 0, comma;

        comma = line.find(',', pos);
        int id = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        comma = line.find(',', pos);
        string plate = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        string brand = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        string model = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        string type = line.substr(pos, comma - pos);
        pos = comma + 1;

        comma = line.find(',', pos);
        double price = stod(line.substr(pos, comma - pos));
        pos = comma + 1;

        CarStatus status = (CarStatus)stoi(line.substr(pos));

        Car* car = new Car(id, plate, brand, model, type, price, status);
        cars.pushBack(car);

        if (id > maxId)
            maxId = id;
    }

    Car::syncNextId(maxId);
    file.close();
    cout << "✅ Cars loaded from CSV\n";
}
