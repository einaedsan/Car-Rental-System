#pragma once
#include <iostream>
#include "UserList.h"
// Forward declarations
class Fleet;
class ReservationPriorityQueue;
class RentalQueue;

class StaffMenu {
public:
    static void show(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals, UserList& users);


};
