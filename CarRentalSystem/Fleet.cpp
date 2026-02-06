#include "Fleet.h"
#include "Car.h"
#include <iostream>

using namespace std;

Fleet::Fleet() {}


void Fleet::addCar(Car* car) {
    if (!car) return;

    cars.pushBack(car);
    index.insert(car->getId(), car);
}

CarList& Fleet::getCarList() {
    return cars;
}

void Fleet::showCarList() const {
    CarNode* cur = cars.getHead();

    if (!cur) {
        cout << "No cars available.\n";
        return;
    }

    cout << "ID | Name | Status\n";
    cout << "---------------------------\n";

    while (cur) {
        Car* car = cur->data;
        cout << car->getId() << " | "
            << car->getBrand() << " | "
            << car->getPricePerDay() << " | "
            << endl;

        cur = cur->next;
    }
}


void Fleet::showCarDetails(int carId) const {
    Car* car = index.search(carId);

    if (!car) {
        cout << "Car not found.\n";
        return;
    }

    cout << "===== Car Details =====\n";
    cout << "ID: " << car->getId() << endl;
    cout << "Plate: " << car->getPlate() << endl;
    cout << "Brand: " << car->getBrand() << endl;
    cout << "Model: " << car->getModel() << endl;
    cout << "Type: " << car->getType() << endl;
    cout << "Price per day: " << car->getPricePerDay() << endl;
    cout << "Status: " << car->getStatus() << endl;

    if (car->getStatus() == RENTED) {
        cout << "Expected return day: (from Rental)\n";
    }
}

void Fleet::filterCars(const char* brand, const char* type, double maxPrice) const {

    CarNode* cur = cars.getHead();
    bool found = false;

    cout << "Filtered results:\n";

    while (cur) {
        Car* car = cur->data;

        bool brandOk = (!brand || car->getBrand() == brand);
        bool typeOk = (!type || car->getType() == type);
        bool priceOk = (maxPrice <= 0 || car->getPricePerDay() <= maxPrice);

        if (brandOk && typeOk && priceOk) {
            cout << car->getId()
                << " - "
                << car->getBrand() << " "
                << car->getModel()
                << endl;
            found = true;
        }

        cur = cur->next;
    }

    if (!found) {
        cout << "No cars match the filter.\n";
    }
}

void Fleet::showAllBrands() const {
    CarNode* cur = cars.getHead();
    string shown[500];
    int count = 0;

    cout << "Available Brands:\n";

    while (cur) {
        string brand = cur->data->getBrand();
        bool exists = false;

        for (int i = 0; i < count; i++) {
            if (shown[i] == brand) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            cout << "- " << brand << endl;
            shown[count++] = brand;
        }

        cur = cur->next;
    }
}

void Fleet::showAllTypes() const {
    CarNode* cur = cars.getHead();
    string shown[500];
    int count = 0;

    cout << "Available Types:\n";

    while (cur) {
        string type = cur->data->getType();
        bool exists = false;

        for (int i = 0; i < count; i++) {
            if (shown[i] == type) {
                exists = true;
                break;
            }
        }

        if (!exists) {
            cout << "- " << type << endl;
            shown[count++] = type;
        }

        cur = cur->next;
    }
}

void Fleet::showCarsByBrand(const string& brand) const {
    CarNode* cur = cars.getHead();
    bool found = false;

    while (cur) {
        Car* car = cur->data;
        if (car->getBrand() == brand) {
            cout << car->getId()
                << " - "
                << car->getBrand() << " "
                << car->getModel()
                << endl;
            found = true;
        }
        cur = cur->next;
    }

    if (!found)
        cout << "No cars found for this brand.\n";
}

void Fleet::showCarsByType(const string& type) const {
    CarNode* cur = cars.getHead();
    bool found = false;

    while (cur) {
        Car* car = cur->data;
        if (car->getType() == type) {
            cout << car->getId()
                << " - "
                << car->getBrand() << " "
                << car->getModel()
                << endl;
            found = true;
        }
        cur = cur->next;
    }

    if (!found)
        cout << "No cars found for this type.\n";
}


Car* Fleet::findCarById(int carId) {
    return index.search(carId);
}
