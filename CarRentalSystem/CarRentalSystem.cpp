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

#include <iostream>

using namespace std;

int main() {
    // 🧑‍🤝‍🧑 کاربران و ماشین‌ها
    UserList users;
    Fleet fleet;

    // 🗓 رزروها و اجاره‌ها
    ReservationPriorityQueue reservations;
    RentalQueue rentals;
    MaintenanceList maintenances;

    // 🚗 Load Cars into Fleet
    FleetStorage::loadCars(fleet, "cars.csv");

    // 📦 Load Rentals و وصل کردن ماشین‌ها به حالت RENTED
    RentalStorage::loadFromCSV(rentals, "rentals.csv");

    RentalQueueNode* curR = rentals.frontNode();
    while (curR) {
        Rental* r = curR->rental;
        Car* car = fleet.findCarById(r->getCarId());
        if (car)
            car->setStatus(RENTED);
        curR = curR->next;
    }

    // 📦 Load Reservations و وصل کردن به ماشین‌ها
    ReservationStorage::loadFromCSV(reservations, "reservations.csv");

    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* res = reservations.getAt(i);
        Car* car = fleet.findCarById(res->getCarId());
        if (car) {
            car->getReservationQueue().addReservation(res);

            // فقط اگر ماشین آزاد بود و Rental نداشت، وضعیت رو RESERVED کن
            if (car->getStatus() == AVAILABLE)
                car->setStatus(RESERVED);
        }
    }

    // 🛠 Load Maintenance و وصل کردن به ماشین‌ها
    MaintenanceStorage::load(maintenances, "maintenance.csv");

    MaintenanceNode* curM = maintenances.getHead();
    while (curM) {
        Maintenance* m = curM->data;
        Car* car = fleet.findCarById(m->getCarId());
        if (car)
            car->getMaintenanceHistory()->addMaintenance(m);
        curM = curM->next;
    }

    // 👤 Load users
    UserStorage::loadFromCSV(users, "users.csv");

    // 🎮 Run Guest Menu
    GuestMenu::show(users, fleet, reservations, rentals);

    // 👨‍💼 Run Staff Menu بعد از GuestMenu (اختیاری برای تست Staff)
    StaffMenu staffMenu;
    staffMenu.show(fleet, reservations, rentals);

    // 💾 Save data on exit
    UserStorage::saveToCSV(users, "users.csv");
    FleetStorage::saveCars(fleet, "cars.csv");
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    ReservationStorage::saveToCSV(reservations, "reservations.csv");

    return 0;
}



//#include "UserList.h"
//#include "UserStorage.h"
//#include "GuestMenu.h"
//
//#include "Fleet.h"
//#include "FleetStorage.h"
//
//#include "RentalQueue.h"
//#include "RentalStorage.h"
//
//#include "ReservationPriorityQueue.h"
//#include "ReservationStorage.h"
//
//#include "MaintenanceStorage.h"
//
//int main() {
//    UserList users;
//    Fleet fleet;
//
//    ReservationPriorityQueue reservations;
//    RentalQueue rentals;
//    MaintenanceList maintenances;
//
//    // 🚗 Load Cars into Fleet
//    FleetStorage::loadCars(fleet, "cars.csv");
//
//    // 📦 Load Rentals
//    RentalStorage::loadFromCSV(rentals, "rentals.csv");
//
//    // 📦 Load Reservations
//    ReservationStorage::loadFromCSV(reservations, "reservations.csv");
//
//    // 🔗 وصل کردن Rentals به Fleet
//    RentalQueueNode* curR = rentals.frontNode();
//    while (curR) {
//        Rental* r = curR->rental;
//        Car* car = fleet.findCarById(r->getCarId());
//        if (car)
//            car->setStatus(RENTED);
//        curR = curR->next;
//    }
//
//    // 🔗 وصل کردن Reservations به Fleet
//    for (int i = 0; i < reservations.getSize(); i++) {
//        Reservation* res = reservations.getAt(i);
//        Car* car = fleet.findCarById(res->getCarId());
//        if (car && car->getStatus() == AVAILABLE)
//            car->setStatus(RESERVED);
//    }
//    // 🚗 Load Cars into Fleet
//    FleetStorage::loadCars(fleet, "cars.csv");
//
//    // 📦 Load Reservations
//    ReservationPriorityQueue reservations;
//    ReservationStorage::loadFromCSV(reservations, "reservations.csv");
//
//    // 🔗 وصل کردن Reservations به Fleet
//    for (int i = 0; i < reservations.getSize(); i++) {
//        Reservation* res = reservations.getAt(i);
//        Car* car = fleet.findCarById(res->getCarId());
//        if (car) {
//            car->getReservationQueue().addReservation(res); // ← مهم: اینجاست که رزروها به ماشین وصل میشن
//            if (car->getStatus() == AVAILABLE)   // اگه ماشین آزاد بود، وضعیتشو RESERVED کن
//                car->setStatus(RESERVED);
//        }
//    }
//
//
//    // 🛠 Load Maintenance
//    MaintenanceStorage::load(maintenances, "maintenance.csv");
//
//    // 🔗 وصل کردن Maintenance به ماشین داخل Fleet
//    MaintenanceNode* curM = maintenances.getHead();
//    while (curM) {
//        Maintenance* m = curM->data;
//        Car* car = fleet.findCarById(m->getCarId());
//        if (car) {
//            car->getMaintenanceHistory()->addMaintenance(m);
//        }
//        curM = curM->next;
//    }
//
//    // 👤 Load users
//    UserStorage::loadFromCSV(users, "users.csv");
//
//    // 🎮 Run app
//    GuestMenu::show(users, fleet, reservations, rentals);
//
//    // 💾 Save on exit
//    UserStorage::saveToCSV(users, "users.csv");
//    FleetStorage::saveCars(fleet, "cars.csv");
//
//    return 0;
//}
