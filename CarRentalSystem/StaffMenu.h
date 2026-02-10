#pragma once
#include <iostream>

// Forward declarations
class Fleet;
class ReservationPriorityQueue;
class RentalQueue;

class StaffMenu {
public:
    static void show(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals);
};
