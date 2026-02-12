#include "Staff.h"
#include <iostream>
#include "RentalStorage.h"
#include "FleetStorage.h"
#include"ReservationStorage.h"
#include "MaintenanceStorage.h"
#include "UserStorage.h"



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

//void Staff::processCarReturn(Fleet& fleet, RentalQueue& rentals, UserList& users) {
//    if (rentals.isEmpty()) {
//        cout << "No rentals to process.\n";
//        return;
//    }
//
//    cout << "\n===== Active Rentals =====\n";
//    rentals.showActiveRentals();
//
//    int rentalId;
//    cout << "\nEnter Rental ID to return: ";
//    cin >> rentalId;
//
//    Rental* rent = rentals.findById(rentalId);
//    if (!rent || !rent->isActive()) {
//        cout << "Invalid or already closed rental.\n";
//        return;
//    }
//
//    Car* car = fleet.findCarById(rent->getCarId());
//    if (!car) {
//        cout << "Car not found.\n";
//        return;
//    }
//
//    User* user = users.findById(rent->getUserId());
//
//    cout << "\nReturning Car:\n";
//    cout << "Car ID: " << car->getId() << "\n";
//    cout << "Plate: " << car->getPlate() << "\n";
//    cout << "Brand: " << car->getBrand() << "\n";
//    cout << "Model: " << car->getModel() << "\n";
//    cout << "Start Day: " << rent->getStartDay() << "\n";
//    cout << "Expected Return Day: " << rent->getExpectedReturnDay() << "\n";
//
//    // ------------------------
//    // محاسبه هزینه و جریمه
//    int daysRented = SystemDate::getDay() - rent->getStartDay() + 1;
//    double baseCost = daysRented * car->getPricePerDay();
//    double lateFine = 0;
//    if (SystemDate::getDay() > rent->getExpectedReturnDay())
//        lateFine = (SystemDate::getDay() - rent->getExpectedReturnDay()) * SystemConfig::DAILY_LATE_FINE;
//
//    rent->setTotalCost(baseCost);
//    rent->setLateFine(lateFine);
//
//    // اضافه کردن بدهی به کاربر
//    if (user) user->addDebt(baseCost + lateFine);
//
//    rent->setActualReturnDay(SystemDate::getDay());
//    rent->closeRental();
//
//    // ------------------------
//    // ✅ آپدیت وضعیت ماشین با متد جدید
//    car->updateStatus(rentals);  // این خط جایگزین تمام if/else قبلی شد
//
//    // ------------------------
//    // نمایش نتیجه
//    cout << "\nRental Closed Successfully!\n";
//    cout << "Total Cost: " << rent->getTotalCost() << "\n";
//    cout << "Late Fine: " << rent->getLateFine() << "\n";
//    if (user)
//        cout << "Your total debt is now: " << user->getDebt() << "\n";
//
//    // ------------------------
//    // ذخیره فایل‌ها
//    FleetStorage::saveCars(fleet, "cars.csv");
//    RentalStorage::saveToCSV(rentals, "rentals.csv");
//    UserStorage::saveToCSV(users, "users.csv");
//}
void Staff::processCarReturn(Fleet& fleet, RentalQueue& rentals, UserList& users) {
    if (rentals.isEmpty()) {
        cout << "No rentals to process.\n";
        return;
    }

    cout << "\n===== Active Rentals =====\n";
    rentals.showActiveRentals();

    int rentalId;
    cout << "\nEnter Rental ID to return: ";
    cin >> rentalId;

    Rental* rent = rentals.findById(rentalId);
    if (!rent || !rent->isActive()) {
        cout << "Invalid or already closed rental.\n";
        return;
    }

    Car* car = fleet.findCarById(rent->getCarId());
    if (!car) {
        cout << "Car not found.\n";
        return;
    }

    User* user = users.findById(rent->getUserId());

    // گرفتن روز واقعی برگشت
    int actualReturnDay;
    cout << "Enter actual return day for this rental: ";
    cin >> actualReturnDay;

    if (actualReturnDay < rent->getStartDay()) {
        cout << "Error: Actual return day cannot be before start day.\n";
        return;
    }

    rent->setActualReturnDay(actualReturnDay);

    // نمایش اطلاعات اجاره و خودرو
    cout << "\nReturning Car:\n";
    cout << "Car ID: " << car->getId() << "\n";
    cout << "Plate: " << car->getPlate() << "\n";
    cout << "Brand: " << car->getBrand() << "\n";
    cout << "Model: " << car->getModel() << "\n";
    cout << "Start Day: " << rent->getStartDay() << "\n";
    cout << "Expected Return Day: " << rent->getExpectedReturnDay() << "\n";
    cout << "Actual Return Day: " << rent->getActualReturnDay() << "\n";

    // محاسبه هزینه پایه
    int daysRented = actualReturnDay - rent->getStartDay() + 1;
    double baseCost = daysRented * car->getPricePerDay();

    // محاسبه جریمه دیرکرد
    int lateDays = 0;
    double lateFine = 0;
    if (actualReturnDay > rent->getExpectedReturnDay()) {
        lateDays = actualReturnDay - rent->getExpectedReturnDay();
        lateFine = lateDays * SystemConfig::DAILY_LATE_FINE; // این عدد میتونه بزرگتر از قیمت روزانه باشه
    }

    rent->setTotalCost(baseCost);
    rent->setLateFine(lateFine);

    // اضافه کردن بدهی به کاربر
    if (user) {
        user->addDebt(baseCost + lateFine);
    }

    rent->closeRental();

    // آپدیت وضعیت ماشین
    car->updateStatus(rentals);

    // نمایش نتیجه
    cout << "\nRental Closed Successfully!\n";
    cout << "Base Cost (Days Rented): " << baseCost << "\n";
    if (lateDays > 0)
        cout << "Late Fine (" << lateDays << " late days): " << lateFine << "\n";
    else
        cout << "Late Fine: 0\n";

    if (user)
        cout << "Your total debt is now: " << user->getDebt() << "\n";

    // ذخیره فایل‌ها
    FleetStorage::saveCars(fleet, "cars.csv");
    RentalStorage::saveToCSV(rentals, "rentals.csv");
    UserStorage::saveToCSV(users, "users.csv");
}

void Staff::finishMaintenance(Fleet& fleet) {
    int carId;

    fleet.showCarList();
    std::cout << "Enter Car ID to finish maintenance (0 to cancel): ";
    std::cin >> carId;

    if (carId == 0)
        return;

    Car* car = fleet.findCarById(carId);

    if (!car) {
        std::cout << "Car not found!\n";
        return;
    }

    if (car->getStatus() != MAINTENANCE) {
        std::cout << "Car is not under maintenance.\n";
        return;
    }

    // ✅ آخرین Maintenance pending را تمام کن
    if (car->getMaintenanceHistory()) {
        MaintenanceNode* cur = car->getMaintenanceHistory()->getHead();
        while (cur) {
            if (!cur->data->isFinished())
                cur->data->setFinished(true);
            cur = cur->next;
        }

        // ذخیره Maintenance های ماشین
        MaintenanceStorage::save(*car->getMaintenanceHistory(), "maintenance.csv");
    }

    // تغییر وضعیت ماشین
    car->setStatus(AVAILABLE);
    std::cout << "Car " << car->getId() << " is now AVAILABLE.\n";

    // ذخیره ماشین‌ها
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

void Staff::viewCarMaintenanceHistory(Fleet& fleet) {
    int carId;

    fleet.showCarList();
    cout << "Enter Car ID to view maintenance history (0 to cancel): ";
    cin >> carId;

    if (carId == 0)
        return;

    Car* car = fleet.findCarById(carId);

    if (!car) {
        cout << "Car not found!\n";
        return;
    }

    car->showMaintenanceHistory();
}

