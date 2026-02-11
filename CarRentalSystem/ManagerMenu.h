#pragma once
#include <iostream>
#include "UserStorage.h"
#include "FleetStorage.h"
#include "RentalStorage.h"
#include "MaintenanceStorage.h"
#include "ReservationStorage.h"

class Fleet;
class RentalQueue;
class UserList;
class MaintenanceList;
class ReservationPriorityQueue;

class ManagerMenu {

public:
    static void show(Fleet& fleet, RentalQueue& rentals, UserList& users, MaintenanceList& maintenance, ReservationPriorityQueue& reservations);

};
