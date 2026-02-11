#include "Car.h"

int Car::nextId = 1;

Car::Car(string Plate, string Brand, string Model, string Type, double Price)
{
    id = nextId++;
    plate = Plate;
    brand = Brand;
    model = Model;
    type = Type;
    pricePerDay = Price;
    status = AVAILABLE;
  
    maintenanceHistory = new MaintenanceList();
    totalMaintenanceCost = 0;

}

Car::Car(int Id, string Plate, string Brand, string Model,
    string Type, double Price, CarStatus Status)
    : id(Id), plate(Plate), brand(Brand), model(Model),
    type(Type), pricePerDay(Price), status(Status)
{
    if (Id >= nextId)
        nextId = Id + 1;

    maintenanceHistory = new MaintenanceList();

    totalMaintenanceCost = 0;
}

Car::~Car()
{
    delete maintenanceHistory;
}

int Car::getId() const {
    return id;
}

string Car::getPlate() const{
    return plate;
}

string Car::getBrand() const {
    return brand;
}

string Car::getModel() const {
    return model;
}

string Car::getType() const { 
    return type; 
}

double Car::getPricePerDay() const {
    return pricePerDay;
}

CarStatus Car::getStatus() const {
    return status;
}

void Car::setStatus(CarStatus s) { 
    status = s;
}

//ReservationQueue* Car::getReservationQueue() const {
//    return reservationQueue;
//}
//
MaintenanceList* Car::getMaintenanceHistory() const {
    return maintenanceHistory;
}

void Car::syncNextId(int maxId) {
    nextId = maxId + 1;
}

ReservationPriorityQueue& Car::getReservationQueue() {
    return reservations;
}

bool Car::isAvailable(int startDay, int endDay) const {

    if (status == MAINTENANCE || status == RENTED)
        return false;

    return !reservations.hasConflict(startDay, endDay);
}

void Car::addMaintenance(Maintenance* m)
{
    if (!m) return;

    maintenanceHistory->addMaintenance(m);
    totalMaintenanceCost += m->getCost();
    status = MAINTENANCE; 
}


void Car::loadMaintenance(Maintenance* m) {
    if (!m) return;

    maintenanceHistory->addMaintenance(m);
    totalMaintenanceCost += m->getCost();
    // اینجا status تغییر نمیکنیم چون از فایل لود شده
}

double Car::getTotalMaintenanceCost() const 
{
    return totalMaintenanceCost;
}
