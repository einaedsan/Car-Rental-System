#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include "Fleet.h"
#include "RentalQueue.h"

class Manager : public User {
private:
    static Manager* instance;   

    Manager();                  

public:
    static Manager* getInstance();
    void generateReport(Fleet& fleet, RentalQueue& rentals);
    void exportCSV(Fleet& fleet, RentalQueue& rentals);

};

#endif
