#pragma once
#ifndef STAFF_H
#define STAFF_H

#include "User.h"
#include "Fleet.h"
#include "ReservationPriorityQueue.h"
#include "UserList.h"
#include "RentalQueue.h"

class Staff : public User {
private:
    static Staff* instance;
    Staff(); // private constructor

public:
    static Staff* getInstance();

    // وظایف اصلی Staff
    void convertReservationToRental(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals);
    void processCarReturn(Fleet& fleet, RentalQueue& rentals, UserList& users);
    void processReservationQueue(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals);
    void addEditCar(Fleet& fleet);
    void sendCarToMaintenance(Fleet& fleet);
    void finishMaintenance(Fleet& fleet);
    void registerMaintenance(Fleet& fleet);

};

#endif
