#pragma once
#ifndef CUSTOMER_MENU_H
#define CUSTOMER_MENU_H

#include "User.h"
#include "CarList.h"

class CustomerMenu {
private:
    CarList* carList;

    void createReservation(User* user);
    void viewReservations(User* user);

public:
    CustomerMenu(CarList* list);
    void show(User* user);
};

#endif
