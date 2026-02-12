#include "Maintenance.h"

int Maintenance::nextId = 1;

//Maintenance::Maintenance(int d, int CarId, const string& desc, double c): maintenanceId(nextId++),day(d),carId(CarId), description(desc), cost(c) {}

Maintenance::Maintenance(int day, int carId, const string& description, double cost)
    : day(day), carId(carId), description(description), cost(cost), finished(false)
{
    maintenanceId = nextId++;
}

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
void Maintenance::setFinished(bool f) { finished = f; }
bool Maintenance::isFinished() const { return finished; }