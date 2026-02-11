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
    double totalMaintenanceCost;

    ReservationPriorityQueue reservations;
    MaintenanceList* maintenanceHistory;

public:
    Car(string Plate, string Brand, string Model, string Type, double Price);
    Car(int id, string plate, string brand, string model,
        string type, double price, CarStatus status);

    ~Car();
    int getId() const;
    string getPlate() const;
    string getBrand() const;
    string getModel() const;
    string getType() const;
    double getPricePerDay() const;
    CarStatus getStatus() const;
    // œ«Œ· class Car
    void setBrand(const string& b) { brand = b; }
    void setModel(const string& m) { model = m; }
    void setType(const string& t) { type = t; }
    void setPricePerDay(double p) { pricePerDay = p; }


    void setStatus(CarStatus s);
    static void syncNextId(int maxId);

    ReservationPriorityQueue& getReservationQueue();
    bool isAvailable(int startDay, int endDay) const;

    MaintenanceList* getMaintenanceHistory() const;
    void addMaintenance(Maintenance* m);
    double getTotalMaintenanceCost() const;
    void loadMaintenance(Maintenance* m);
};

#endif
