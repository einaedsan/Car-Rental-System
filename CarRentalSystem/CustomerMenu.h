#pragma once
#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include "User.h"
#include "UserList.h"
#include "Fleet.h"

class CustomerMenu {
public:
    CustomerMenu() = default;  

    void show(User* user, Fleet& fleet,
        RentalQueue& rentals,
        UserList& users);

    void renewRental(User* user, Fleet& fleet, RentalQueue& rentals);
private:
    void createReservation(User* user, Fleet& fleet, RentalQueue& rentals);

    void viewReservations(User* user, Fleet& fleet);
    void payFees(User* user, UserList& users);



};

#endif
