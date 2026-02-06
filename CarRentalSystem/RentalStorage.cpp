#include "RentalStorage.h"
#include <fstream>
#include <iostream>

using namespace std;

void RentalStorage::saveToCSV(const RentalQueue& rentals, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "❌ Cannot open rental file\n";
        return;
    }

    file << "rentalId,userId,carId,startDay,expectedReturnDay,actualReturnDay,dailyCost,totalCost,lateFine\n";

    RentalQueueNode* cur = rentals.frontNode();
    while (cur != nullptr) {
        Rental* r = cur->rental;
        file << r->getId() << ","
            << r->getUserId() << ","
            << r->getCarId() << ","
            << r->getStartDay() << ","
            << r->getExpectedReturnDay() << ","
            << r->getActualReturnDay() << ","
            << r->getDailyCost() << "," // اضافه شده
            << r->getTotalCost() << ","
            << r->getLateFine() << "\n";

        cur = cur->next;
    }

    file.close();
    cout << "✅ Rentals saved to CSV\n";
}

void RentalStorage::loadFromCSV(RentalQueue& rentals, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "⚠️ Rental CSV not found, starting empty\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    int maxId = 0;

    while (getline(file, line)) {
        int pos = 0, comma;

        // parse rentalId
        comma = line.find(',', pos);
        int rentalId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse userId
        comma = line.find(',', pos);
        int userId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse carId
        comma = line.find(',', pos);
        int carId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse startDay
        comma = line.find(',', pos);
        int start = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse expectedReturnDay
        comma = line.find(',', pos);
        int expected = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse actualReturnDay
        comma = line.find(',', pos);
        int actual = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse dailyCost
        comma = line.find(',', pos);
        double dailyCost = stod(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse totalCost
        comma = line.find(',', pos);
        double total = stod(line.substr(pos, comma - pos));
        pos = comma + 1;

        // parse lateFine
        double fine = stod(line.substr(pos));

        // ایجاد Rental با dailyCost
        Rental* r = new Rental(userId, carId, start, expected, dailyCost);

        // تنظیم ID واقعی
        r->setRentalId(rentalId);

        // بستن اجاره و محاسبه جریمه و totalCost
        r->closeRental(actual, dailyCost); // روز جریمه = dailyCost یا میتونی مقدار جدا بذاری

        // فقط اطمینان از totalCost و lateFine (اگر لازم باشه از CSV)
        r->setTotalCost(total);
        r->setLateFine(fine);

        rentals.enqueue(r);

        if (rentalId > maxId)
            maxId = rentalId;
    }

    // همگام سازی nextId
    Rental::syncNextId(maxId);

    file.close();
    cout << "✅ Rentals loaded from CSV\n";
}
