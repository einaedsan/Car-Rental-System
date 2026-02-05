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
    //reservationQueue = nullptr;
    //maintenanceHistory = nullptr;

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

//ReservationQueue* Car::getReservationQueue() const{
//    return reservationQueue;
//}
//
//MaintenanceList* Car::getMaintenanceHistory() const {
//    return maintenanceHistory;
//}