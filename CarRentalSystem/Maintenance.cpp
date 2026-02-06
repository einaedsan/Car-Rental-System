#include "Maintenance.h"

int Maintenance::nextId = 1;

Maintenance::Maintenance(int d, int CarId, const string& desc, double c): maintenanceId(nextId++),day(d),carId(CarId), description(desc), cost(c) {}

int Maintenance::getId() const {
    return maintenanceId;
}

int Maintenance::getCarId() const {
    return carId;
}

int Maintenance::getDay() const {
    return day;
}

string Maintenance::getDescription() const {
    return description;
}

double Maintenance::getCost() const {
    return cost;
}