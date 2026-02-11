#pragma once

#pragma once
#ifndef CAR_H
#define CAR_H

#include "MaintenanceList.h"
#include "ReservationPriorityQueue.h"
#include <string>

using std::string;

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

    ReservationPriorityQueue reservations;
    MaintenanceList* maintenanceHistory;

public:
    Car(string Plate, string Brand, string Model, string Type, double Price);
    Car(int id, string plate, string brand, string model,
        string type, double price, CarStatus status);

    int getId() const;
    string getPlate() const;
    string getBrand() const;
    string getModel() const;
    string getType() const;
    double getPricePerDay() const;
    CarStatus getStatus() const;

    void setStatus(CarStatus s);
    static void syncNextId(int maxId);

    ReservationPriorityQueue& getReservationQueue();
    bool isAvailable(int startDay, int endDay) const;

    MaintenanceList* getMaintenanceHistory() const;
};

#endif
