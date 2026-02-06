#pragma once
#ifndef MAINTENANCE_H
#define MAINTENANCE_H

#include <string>
using std::string;

class Maintenance {
private:
    static int nextId;
    int maintenanceId;
    int carId;
    int day;
    string description;
    double cost;

public:

    Maintenance(int day,int CarId, const string& description, double cost);

    int getarId() const;
    int getId() const;
    int getDay() const;
    string getDescription() const;
    double getCost() const;
};

#endif
