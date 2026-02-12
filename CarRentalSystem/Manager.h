#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "User.h"
#include "Fleet.h"
#include "RentalQueue.h"
#include "UserList.h"
#include "MaintenanceList.h"
#include "ReservationPriorityQueue.h"

class Manager : public User {
private:
    static Manager* instance;   

    Manager();                  

public:
    static Manager* getInstance();
    void generateReport(Fleet& fleet, RentalQueue& rentals);
    void exportAllData(Fleet& fleet,UserList& users, RentalQueue& rentals,MaintenanceList& maintenance,ReservationPriorityQueue& reservations);
    void importAllData(Fleet& fleet,UserList& users,RentalQueue& rentals,MaintenanceList& maintenance,ReservationPriorityQueue& reservations);


};

#endif
