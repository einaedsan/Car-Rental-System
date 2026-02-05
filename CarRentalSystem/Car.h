#pragma once
#ifndef CAR_H
#define CAR_H

#include <string>
using std::string;

//class ReservationQueue;
//class MaintenanceList;

enum CarStatus {
    AVAILABLE,
    RESERVED,
    RENTED,
    MAINTENANCE
};

class Car {
private:
    static int nextId;
    int id;
    string plate;
    string brand;
    string model;
    string type;
    double pricePerDay;
    CarStatus status;

    //ReservationQueue* reservationQueue;
    //MaintenanceList* maintenanceHistory;

public:
    //Car();
    Car(string Plate,string Brand, string Model, string Type, double Price);

    int getId() const;
    string getPlate() const;
    string getBrand() const;
    string getModel() const;
    string getType() const;
    double getPricePerDay() const;
    CarStatus getStatus() const;
    void setStatus(CarStatus s);

    //ReservationQueue* getReservationQueue() const;
    //MaintenanceList* getMaintenanceHistory() const;
};

#endif