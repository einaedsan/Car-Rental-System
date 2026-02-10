#include "UserList.h"
#include "UserStorage.h"
#include "GuestMenu.h"
#include "CarStorage.h"
#include "UserList.h"
#include "RentalQueue.h"
#include "ReservationStorage.h"
#include "ReservationPriorityQueue.h"
#include "RentalStorage.h"
#include "MaintenanceStorage.h"
#include "Fleet.h"

int main() {
    UserList users;
    Fleet fleet;
    CarList cars;
    ReservationPriorityQueue reservations;
    RentalQueue rentals;
    CarStorage::loadFromCSV(cars, "cars.csv");

    RentalStorage::loadFromCSV(rentals, "rentals.csv");

    ReservationStorage::loadFromCSV(reservations, "reservations.csv");

    // 🔗 اتصال Rentals به Car
    RentalQueueNode* curR = rentals.frontNode();
    while (curR) {
        Rental* r = curR->rental;
        Car* car = cars.findById(r->getCarId());
        if (car)
            car->setStatus(RENTED);
        curR = curR->next;
    }

    // 🔗 اتصال Reservations به Car
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* res = reservations.getAt(i);
        Car* car = cars.findById(res->getCarId());
        if (car && car->getStatus() == AVAILABLE)
            car->setStatus(RESERVED);
    }

    MaintenanceList maintenances;
    MaintenanceStorage::load(maintenances, "maintenance.csv");

    // 🔗 وصل کردن maintenance به ماشین مناسب
    MaintenanceNode* cur = maintenances.getHead();
    while (cur) {
        Maintenance* m = cur->data;
        Car* car = cars.findById(m->getCarId());
        if (car) {
            car->getMaintenanceHistory()->addMaintenance(m);
        }
        cur = cur->next;
    }
    // Load users from CSV
    UserStorage::loadFromCSV(users, "users.csv");

    // Show guest menu

    GuestMenu::show(users, fleet, reservations, rentals);

    // Save users on exit
    UserStorage::saveToCSV(users, "users.csv");

    return 0;
}
