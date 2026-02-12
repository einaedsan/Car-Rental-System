#include "UserList.h"
#include "UserStorage.h"
#include "GuestMenu.h"
#include "StaffMenu.h"
#include "Fleet.h"
#include "FleetStorage.h"
#include "RentalQueue.h"
#include "RentalStorage.h"
#include "ReservationPriorityQueue.h"
#include "ReservationStorage.h"
#include "MaintenanceStorage.h"
#include "MaintenanceList.h"

#include <iostream>

using namespace std;

int main() {
    UserList users;
    Fleet fleet;

    ReservationPriorityQueue reservations;
    RentalQueue rentals;
    MaintenanceList maintenances;

    // Load cars
    FleetStorage::loadCars(fleet, "cars.csv");
    cout << "\n=== Loaded Fleet ===\n";
    fleet.showCarList();

    // Load rentals
    RentalStorage::loadFromCSV(rentals, "rentals.csv");

    RentalQueueNode* curR = rentals.frontNode();
    while (curR) {
        Rental* r = curR->rental;
        Car* car = fleet.findCarById(r->getCarId());
        if (!car) { curR = curR->next; continue; }

        if (r->isActive()) {
            car->setStatus(RENTED);
        }
        else {
            if (!car->getReservationQueue().isEmpty())
                car->setStatus(RESERVED);
            else if (car->getMaintenanceHistory() && car->getMaintenanceHistory()->hasPendingMaintenance())
                car->setStatus(MAINTENANCE);
            else
                car->setStatus(AVAILABLE);
        }

        curR = curR->next;
    }

    // Load reservations
    ReservationStorage::loadFromCSV(reservations, "reservations.csv");

    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* res = reservations.getAt(i);
        Car* car = fleet.findCarById(res->getCarId());
        if (car) {
            car->getReservationQueue().addReservation(res);

            if (car->getStatus() == AVAILABLE)
                car->setStatus(RESERVED);
        }
    }

    // Load maintenance
    MaintenanceStorage::load(maintenances, "maintenance.csv");
    MaintenanceNode* curM = maintenances.getHead();
    while (curM) {
        Maintenance* m = curM->data;
        Car* car = fleet.findCarById(m->getCarId());
        if (car) car->loadMaintenance(m);
        curM = curM->next;
    }

    // Load users
    UserStorage::loadFromCSV(users, "users.csv");

    // ===============================
    // نمایش داده‌ها برای تست
    // ===============================
   /* cout << "\n=== Rentals Loaded ===\n";
    curR = rentals.frontNode();
    while (curR) {
        Rental* r = curR->rental;
        cout << "Rental ID: " << r->getId()
            << " | Car ID: " << r->getCarId()
            << " | Active: " << (r->isActive() ? "Yes" : "No") << "\n";
        curR = curR->next;
    }

    cout << "\n=== Reservations Loaded ===\n";
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* r = reservations.getAt(i);
        cout << "Reservation ID: " << r->getReservationId()
            << " | Car ID: " << r->getCarId()
            << " | Start: " << r->getStartDay()
            << " | End: " << r->getEndDay() << "\n";
    }

    cout << "\n=== Users Loaded ===\n";
    UserNode* uNode = users.getHead();
    while (uNode) {
        User* u = uNode->data;
        cout << u->getId() << " | " << u->getName() << "\n";
        uNode = uNode->next;
    }*/

    // Guest menu
    GuestMenu::show(users, fleet, reservations, rentals, maintenances);

    // Staff menu
    StaffMenu staffMenu;
    staffMenu.show(fleet, reservations, rentals, users);

    // Save on exit
    UserStorage::saveToCSV(users, "users.csv");
    FleetStorage::saveCars(fleet, "cars.csv");
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    ReservationStorage::saveToCSV(reservations, "reservations.csv");

    return 0;
}
