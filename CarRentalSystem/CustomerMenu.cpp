#include "CustomerMenu.h"
#include <iostream>
#include "CustomerMenu.h"
#include "CarList.h"
#include "Car.h"
#include "CarNode.h"
#include "ReservationPriorityQueue.h"
#include "Reservation.h"
#include "ReservationStorage.h"

//CustomerMenu::CustomerMenu(CarList* list) {
//    carList = list;
//}

void CustomerMenu::show(User* user, Fleet& fleet) {
    bool exitMenu = false;

    while (!exitMenu) {
        std::cout << "\n=== Customer Menu ===\n";
        std::cout << "1. Create Reservation\n";
        std::cout << "2. View Reservations\n";
        std::cout << "3. Renew Rental\n";
        std::cout << "4. Pay Fees\n";
        std::cout << "0. Logout\n";
        std::cout << "Select option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1:
            createReservation(user, fleet);  // از Fleet استفاده می‌کنه
            break;
        case 2:
            viewReservations(user, fleet);   // همین‌طور
            break;
        case 3:
            std::cout << "Renew Rental not implemented yet.\n";
            break;
        case 4:
            std::cout << "Pay Fees not implemented yet.\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}

void CustomerMenu::createReservation(User* user, Fleet& fleet) {
    std::cout << "\n--- Create Reservation ---\n";

    CarNode* cur = fleet.getCarList().getHead();
    while (cur) {
        Car* car = cur->data;
        std::cout << "Car ID: " << car->getId()
            << " | Brand: " << car->getBrand()
            << " | Model: " << car->getModel()
            << " | Price/day: " << car->getPricePerDay()
            << " | Status: ";

        switch (car->getStatus()) {
        case AVAILABLE: std::cout << "Available"; break;
        case RESERVED: std::cout << "Reserved"; break;
        case RENTED: std::cout << "Rented"; break;
        case MAINTENANCE: std::cout << "Maintenance"; break;
        }

        std::cout << "\n";
        cur = cur->next;
    }

    int carId;
    std::cout << "Enter Car ID: ";
    std::cin >> carId;

    Car* selectedCar = fleet.findCarById(carId);
    if (!selectedCar) {
        std::cout << "Car not found!\n";
        return;
    }
    if (selectedCar->getStatus() == MAINTENANCE) {
        std::cout << "Car is under maintenance.\n";
        return;
    }

    int startDay, endDay;
    std::cout << "Enter start day: ";
    std::cin >> startDay;
    std::cout << "Enter end day: ";
    std::cin >> endDay;

    if (startDay >= endDay) {
        std::cout << "Invalid date range!\n";
        return;
    }

    if (!selectedCar->isAvailable(startDay, endDay)) {
        std::cout << "Car already reserved in this period.\n";
        return;
    }

    Reservation* r = new Reservation(user->getId(), selectedCar->getId(), startDay, endDay);
    selectedCar->getReservationQueue().addReservation(r);

    std::cout << "Reservation created successfully!\n";
    std::cout << "Reservation ID: " << r->getReservationId() << "\n";

    ReservationStorage::saveToCSV(selectedCar->getReservationQueue(), "reservations.csv");
}

void CustomerMenu::viewReservations(User* user, Fleet& fleet) {
    std::cout << "\n--- Your Reservations ---\n";
    bool found = false;

    CarNode* carNode = fleet.getCarList().getHead();
    while (carNode) {
        Car* car = carNode->data;
        ReservationPriorityQueue& q = car->getReservationQueue();

        for (int i = 0; i < q.getSize(); i++) {
            Reservation* r = q.getAt(i);
            if (r->getUserId() == user->getId()) {
                std::cout << "Reservation ID: " << r->getReservationId()
                    << " | Car ID: " << r->getCarId()
                    << " | From day " << r->getStartDay()
                    << " to " << r->getEndDay() << "\n";
                found = true;
            }
        }

        carNode = carNode->next;
    }

    if (!found)
        std::cout << "No reservations found.\n";
}
