#include "Maintenance.h"

int Maintenance::nextId = 1;

Maintenance::Maintenance(int d, const string& desc, double c): maintenanceId(nextId++),day(d),description(desc),cost(c) {}

int Maintenance::getId() const {
    return maintenanceId;
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