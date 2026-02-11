#include "Staff.h"
#include <iostream>
#include "RentalStorage.h"
#include "FleetStorage.h"
#include"ReservationStorage.h"
#include "MaintenanceStorage.h"


using namespace std;

// Singleton
Staff* Staff::instance = NULL;

Staff::Staff() : User("staff", "123staff") {}

Staff* Staff::getInstance() {
    if (instance == NULL)
        instance = new Staff();
    return instance;
}


void Staff::processReservationQueue(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals) {
    bool processedAny = false;

    // حلقه تا زمانی که صف خالی نشود
    while (!reservations.isEmpty()) {
        Reservation* r = reservations.getAt(0); // نفر اول در صف
        Car* car = fleet.findCarById(r->getCarId());

        // اگر ماشین موجود و آزاد باشد
        if (car && car->getStatus() == AVAILABLE) {
            // ساخت Rental به مدت 3 روز (یا هر تعداد روز دلخواه)
            Rental* rental = new Rental(r->getUserId(), car->getId(), r->getStartDay(), r->getStartDay() + 3, car->getPricePerDay());
            rentals.enqueue(rental);

            // تغییر وضعیت ماشین
            car->setStatus(RENTED);

            // حذف رزرو از صف
            reservations.popNext();

            cout << "✅ Reservation " << r->getReservationId()
                << " assigned to user " << r->getUserId()
                << " for Car ID " << car->getId() << " for 3 days.\n";

            processedAny = true;
        }
        else {
            // ماشین رزرو شده هنوز آزاد نیست، برو سراغ بعدی
            break; // یا اگر میخوای همه رزروها رو چک کن، continue
        }
    }

    if (!processedAny) {
        cout << "No reservations could be processed right now.\n";
    }
}

void Staff::addEditCar(Fleet& fleet) {
    int choice;
    cout << "1. Add new car\n2. Edit existing car\nSelect option: ";
    cin >> choice;

    if (choice == 1) { // اضافه کردن
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
    else if (choice == 2) { // ویرایش
        int carId;

        fleet.showCarList();
        cout << "Enter Car ID to edit: ";
        cin >> carId;

        Car* car = fleet.findCarById(carId);
        if (!car) {
            cout << "Car not found!\n";
            return;
        }

        string brand, model, type;
        double price;

        cout << "Enter new brand (current: " << car->getBrand() << "): ";
        cin >> brand;
        cout << "Enter new model (current: " << car->getModel() << "): ";
        cin >> model;
        cout << "Enter new type (current: " << car->getType() << "): ";
        cin >> type;
        cout << "Enter new price per day (current: " << car->getPricePerDay() << "): ";
        cin >> price;

        car->setBrand(brand);
        car->setModel(model);
        car->setType(type);
        car->setPricePerDay(price);

        cout << "✅ Car updated successfully!\n";
    }
    else {
        cout << "Invalid option!\n";
        return;
    }

    // ذخیره خودکار بعد از افزودن یا ویرایش
    FleetStorage::saveCars(fleet, "cars.csv");
}


void Staff::convertReservationToRental(Fleet& fleet, ReservationPriorityQueue& reservations, RentalQueue& rentals) {
    if (reservations.isEmpty()) {
        std::cout << "No reservations to convert.\n";
        return;
    }


    std::cout << "=== Reservations ===\n";
    for (int i = 0; i < reservations.getSize(); i++) {
        Reservation* r = reservations.getAt(i);
        Car* c = fleet.findCarById(r->getCarId());
        if (!c) continue;

        std::cout << "Reservation ID: " << r->getReservationId()
            << ", Car ID: " << c->getId()
            << ", Brand: " << c->getBrand()
            << ", Model: " << c->getModel()
            << ", Status: " << c->getStatus() << "\n";
    }

    int chosenCarId;
    std::cout << "Enter Car ID to convert reservation to rental (0 to cancel): ";
    std::cin >> chosenCarId;
    if (chosenCarId == 0) return;

    // پیدا کردن رزرو برای این ماشین
    Reservation* res = nullptr;
    for (int i = 0; i < reservations.getSize(); i++) {
        if (reservations.getAt(i)->getCarId() == chosenCarId) {
            res = reservations.getAt(i);
            break;
        }
    }

    if (!res) {
        std::cout << "No reservation found for this Car ID.\n";
        return;
    }

    Car* car = fleet.findCarById(chosenCarId);
    if (!car) {
        std::cout << "Car not found!\n";
        return;
    }

    if (car->getStatus() == RENTED || car->getStatus() == MAINTENANCE) {
        std::cout << "Car is not available for rental.\n";
        return;
    }

    // تبدیل به اجاره
    Rental* rent = new Rental(res->getUserId(), car->getId(), res->getStartDay(), res->getEndDay(), car->getPricePerDay());
    rentals.enqueue(rent);

    car->setStatus(RENTED);

    // حذف رزرو از صف
    reservations.popNext(); // یا بهتر: removeById(res->getReservationId());

    std::cout << "Reservation " << res->getReservationId()
        << " for Car " << car->getId()
        << " converted to Rental " << rent->getId() << ".\n";

    // ذخیره خودکار
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    FleetStorage::saveCars(fleet, "cars.csv");
    ReservationStorage::saveToCSV(reservations, "reservations.csv");
}

void Staff::processCarReturn(Fleet& fleet, RentalQueue& rentals) {
    if (rentals.isEmpty()) {
        std::cout << "No rentals to process.\n";
        return;
    }

    Rental* rent = rentals.peek();
    Car* car = fleet.findCarById(rent->getCarId());

    int actualReturn;
    std::cout << "Enter actual return day for rental " << rent->getId() << ": ";
    std::cin >> actualReturn;

    double dailyLateFine = 20.0; // میتونه از تنظیمات پروژه گرفته بشه
    rent->closeRental(actualReturn, dailyLateFine);


    // بررسی تعمیرات
    if (car->getMaintenanceHistory() && car->getMaintenanceHistory()->hasPendingMaintenance())
        car->setStatus(MAINTENANCE);
    else
        car->setStatus(AVAILABLE);

    // حذف Rental از صف و ذخیره
    rentals.dequeue();
    RentalStorage::saveToCSV(rentals, "rentals.csv");

    std::cout << "Rental " << rent->getId() << " closed. Total cost: " << rent->getTotalCost()
        << ", Late fine: " << rent->getLateFine() << "\n";

    // 🔹 ذخیره خودکار بعد از برگشت
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    FleetStorage::saveCars(fleet, "cars.csv");
}


void Staff::sendCarToMaintenance(Fleet& fleet) {
    int carId;

    fleet.showCarList();
    cout << "Enter Car ID to send to maintenance (0 to cancel): ";
    cin >> carId;

    if (carId == 0)
        return;

    Car* car = fleet.findCarById(carId);

    if (!car) {
        cout << "Car not found!\n";
        return;
    }

    if (car->getStatus() == MAINTENANCE) {
        cout << "Car is already under maintenance.\n";
        return;
    }

    if (car->getStatus() == RENTED) {
        cout << "Car is currently rented. Cannot send to maintenance.\n";
        return;
    }

    car->setStatus(MAINTENANCE);

    cout << "Car " << car->getId() << " is now under maintenance.\n";

    FleetStorage::saveCars(fleet, "cars.csv");
}


void Staff::finishMaintenance(Fleet& fleet) {
    int carId;

    fleet.showCarList();
    cout << "Enter Car ID to finish maintenance (0 to cancel): ";
    cin >> carId;

    if (carId == 0)
        return;

    Car* car = fleet.findCarById(carId);

    if (!car) {
        cout << "Car not found!\n";
        return;
    }

    if (car->getStatus() != MAINTENANCE) {
        cout << "Car is not under maintenance.\n";
        return;
    }

    car->setStatus(AVAILABLE);

    cout << "Car " << car->getId() << " is now AVAILABLE.\n";

    FleetStorage::saveCars(fleet, "cars.csv");
}

void Staff::registerMaintenance(Fleet& fleet) {
    int carId;

    fleet.showCarList();
    cout << "Enter Car ID to register maintenance (0 to cancel): ";
    cin >> carId;

    if (carId == 0)
        return;

    Car* car = fleet.findCarById(carId);

    if (!car) {
        cout << "Car not found!\n";
        return;
    }

    int day;
    string description;
    double cost;

    cout << "Enter maintenance day: ";
    cin >> day;

    cin.ignore(); // مهم برای getline

    cout << "Enter description: ";
    getline(cin, description);

    cout << "Enter cost: ";
    cin >> cost;

    // ساخت آبجکت تعمیر
    Maintenance* m = new Maintenance(day, carId, description, cost);

    // اضافه کردن به ماشین
    car->addMaintenance(m);

    cout << "Maintenance registered successfully.\n";

    // ذخیره ماشین‌ها
    FleetStorage::saveCars(fleet, "cars.csv");

    // ذخیره تعمیرات جداگانه
    if (car->getMaintenanceHistory())
        MaintenanceStorage::save(*car->getMaintenanceHistory(), "maintenance.csv");
}


