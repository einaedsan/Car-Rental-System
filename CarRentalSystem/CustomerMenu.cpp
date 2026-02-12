#include "CustomerMenu.h"
#include <iostream>
#include "CustomerMenu.h"
#include "CarList.h"
#include "Car.h"
#include "CarNode.h"
#include "ReservationPriorityQueue.h"
#include "Reservation.h"
#include "ReservationStorage.h"
#include "RentalStorage.h"
#include "UserStorage.h"

//CustomerMenu::CustomerMenu(CarList* list) {
//    carList = list;
//}

void CustomerMenu::show(User* user, Fleet& fleet,
    RentalQueue& rentals,
    UserList& users)

{
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
          createReservation(user, fleet, rentals);
          
            break;
        case 2:
            viewReservations(user, fleet);   // همین‌طور
            break;
        case 3:
            renewRental(user, fleet, rentals);
            break;
        case 4:
            payFees(user, users);
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            std::cout << "Invalid option! Try again.\n";
        }
    }
}

void CustomerMenu::createReservation(User* user, Fleet& fleet, RentalQueue& rentals)
{
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

    if (!selectedCar->isAvailable(startDay, endDay, rentals))
    {
        std::cout << "Car already reserved in this period.\n";
        return;
    }

    Reservation* r = new Reservation(user->getId(), selectedCar->getId(), startDay, endDay);
    selectedCar->getReservationQueue().addReservation(r);
    selectedCar->updateStatus(rentals);


    std::cout << "Reservation created successfully!\n";
    std::cout << "Reservation ID: " << r->getReservationId() << "\n";

    // ذخیره در فایل
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
void CustomerMenu::renewRental(User* user, Fleet& fleet, RentalQueue& rentals) {

    cout << "\n--- Renew Rental ---\n";

    RentalQueueNode* cur = rentals.frontNode();
    bool found = false;

    while (cur) {
        Rental* r = cur->rental;

        if (r->getUserId() == user->getId() && r->isActive()) {

            cout << "Rental ID: " << r->getId()
                << " | Car ID: " << r->getCarId()
                << " | Return Day: " << r->getExpectedReturnDay()
                << "\n";

            found = true;
        }

        cur = cur->next;
    }

    if (!found) {
        cout << "No active rentals found.\n";
        return;
    }

    int rentalId;
    cout << "Enter Rental ID to extend: ";
    cin >> rentalId;

    Rental* rental = rentals.findById(rentalId);

    if (!rental || rental->getUserId() != user->getId() || !rental->isActive()) {
        cout << "Invalid rental.\n";
        return;
    }

    int extraDays;
    cout << "Enter extra days: ";
    cin >> extraDays;

    if (extraDays <= 0) {
        cout << "Invalid number of days.\n";
        return;
    }

    // چک تداخل با رزرو بعدی
    Car* car = fleet.findCarById(rental->getCarId());

    if (!car) {
        cout << "Car not found.\n";
        return;
    }

    int newReturn = rental->getExpectedReturnDay() + extraDays;

    if (!car->isAvailableForPeriod(
        rental->getExpectedReturnDay(),
        newReturn,
        rental->getId()
    )) {
        cout << "Cannot extend. Car reserved in this period.\n";
        return;
    }


        rental->extendRental(extraDays);

        // آپدیت وضعیت ماشین بعد از تمدید
        car->updateStatus(rentals);

        cout << "Rental extended successfully!\n";
        cout << "New Return Day: " << rental->getExpectedReturnDay() << "\n";

        // ذخیره در فایل
        RentalStorage::saveToCSV(rentals, "rentals.csv");

    }


    void CustomerMenu::payFees(User * user, UserList & users)
    {    cout << "\n--- Pay Fees ---\n";

    double debt = user->getDebt();
    if (debt <= 0) {
        cout << GREEN << "You have no outstanding fees.\n" << RESET;
        return;
    }

    cout << YELLOW << "Your current debt: " << debt << RESET << "\n";

    double amount;
    cout << "Enter amount to pay: ";
    cin >> amount;

    if (amount <= 0) {
        cout << RED << "Invalid amount.\n" << RESET;
        return;
    }

    if (amount > debt) amount = debt;

    user->payDebt(amount);

    cout << GREEN << "Payment successful!\n" << RESET;
    cout << "Remaining debt: " << user->getDebt() << "\n";

    if (user->getDebt() == 0)
        user->setBlocked(false);

    UserStorage::saveToCSV(users, "users.csv");
}
