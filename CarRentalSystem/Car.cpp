#include "Car.h"

int Car::nextId = 1;

//Car::Car(): id(0), pricePerDay(0), status(AVAILABLE)) {}

//Car::Car() : id(0), pricePerDay(0), status(AVAILABLE), reservationQueue(NULL), maintenanceHistory(NULL) {}


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

Car::Car(int Id, string Plate, string Brand, string Model,
    string Type, double Price, CarStatus Status)
    : id(Id), plate(Plate), brand(Brand), model(Model),
    type(Type), pricePerDay(Price), status(Status) {

    if (Id >= nextId)
        nextId = Id + 1;
    maintenanceHistory = new MaintenanceList();
}


void Car::syncNextId(int maxId) {
    nextId = maxId + 1;
}

ReservationPriorityQueue& Car::getReservationQueue() {
    return reservations;
}

bool Car::isAvailable(int startDay, int endDay) const {
    return !reservations.hasConflict(startDay, endDay);
}
