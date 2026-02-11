#pragma once
#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include "User.h"
#include "Fleet.h"

class CustomerMenu {
public:
    CustomerMenu() = default;  

    void show(User* user, Fleet& fleet);

private:
    void createReservation(User* user, Fleet& fleet);
    void viewReservations(User* user, Fleet& fleet);
};

#endif
