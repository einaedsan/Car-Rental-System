#include "Staff.h"
#include <iostream>

using namespace std;

// Singleton
Staff* Staff::instance = NULL;

Staff::Staff() : User("staff", "123staff") {}

Staff* Staff::getInstance() {
    if (instance == NULL)
        instance = new Staff();
    return instance;
}

// 1️⃣ تبدیل رزرو به اجاره
void Staff::convertReservationToRental(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals) {
    if (reservations.isEmpty()) {
        cout << "No reservations available.\n";
        return;
    }

    Reservation* r = reservations.popNext(); // حذف نفر اول
    Car* car = fleet.findCarById(r->getCarId());
    if (!car) { cout << "Car not found!\n"; return; }
    if (car->getStatus() != AVAILABLE) { cout << "Car not available!\n"; return; }

    Rental* rental = new Rental(r->getUserId(), car->getId(), r->getStartDay(), r->getEndDay(), car->getPricePerDay());
    rentals.enqueue(rental);
    car->setStatus(RENTED);

    cout << "✅ Reservation converted to Rental!\n";
}

// 2️⃣ بازگشت خودرو
void Staff::processCarReturn(Fleet& fleet, RentalQueue& rentals) {
    int rentalId;
    cout << "Enter Rental ID: "; cin >> rentalId;

    Rental* rental = rentals.findById(rentalId);
    if (!rental) { cout << "Rental not found!\n"; return; }

    Car* car = fleet.findCarById(rental->getCarId());
    if (!car) { cout << "Car not found!\n"; return; }

    int actualReturnDay;
    cout << "Enter actual return day: "; cin >> actualReturnDay;

    rental->closeRental(actualReturnDay, car->getPricePerDay());

    // بررسی تعمیرات
    if (car->getMaintenanceHistory() && car->getMaintenanceHistory()->hasPendingMaintenance())
        car->setStatus(MAINTENANCE);
    else
        car->setStatus(AVAILABLE);

    cout << "✅ Car returned successfully!\n";
}

// 3️⃣ پردازش صف رزرو
void Staff::processReservationQueue(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals) {
    if (reservations.isEmpty()) { cout << "No reservations in queue.\n"; return; }

    Reservation* r = reservations.getAt(0); // فقط نگاه کن
    Car* car = fleet.findCarById(r->getCarId());
    if (!car || car->getStatus() != AVAILABLE) return;

    Rental* rental = new Rental(r->getUserId(), car->getId(), r->getStartDay(), r->getStartDay() + 3, car->getPricePerDay());
    rentals.enqueue(rental);

    car->setStatus(RENTED);
    reservations.popNext(); // حالا حذف می‌کنیم

    cout << "✅ Reservation assigned to user for 3 days.\n";
}

// 4️⃣ افزودن/ویرایش خودرو
void Staff::addEditCar(Fleet& fleet) {
    string plate, brand, model, type;
    double price;

    cout << "Enter plate: "; cin >> plate;
    cout << "Enter brand: "; cin >> brand;
    cout << "Enter model: "; cin >> model;
    cout << "Enter type: "; cin >> type;
    cout << "Enter price per day: "; cin >> price;

    Car* car = new Car(plate, brand, model, type, price);
    fleet.addCar(car);

    cout << "✅ Car added successfully!\n";
}
