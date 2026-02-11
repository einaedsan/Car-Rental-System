#include "RentalStorage.h"
#include <fstream>
#include <iostream>
#include <iomanip> // برای setprecision

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
            << fixed << setprecision(2) << r->getDailyCost() << ","
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

        auto getNextField = [&](string& s) -> string {
            comma = s.find(',', pos);
            string field;
            if (comma == string::npos) {
                field = s.substr(pos);
                pos = s.length();
            }
            else {
                field = s.substr(pos, comma - pos);
                pos = comma + 1;
            }
            return field;
            };

        pos = 0;
        int rentalId = stoi(getNextField(line));
        int userId = stoi(getNextField(line));
        int carId = stoi(getNextField(line));
        int start = stoi(getNextField(line));
        int expected = stoi(getNextField(line));
        int actual = stoi(getNextField(line));
        double dailyCost = stod(getNextField(line));
        double total = stod(getNextField(line));
        double fine = stod(getNextField(line));

        // ایجاد Rental با dailyCost
        Rental* r = new Rental(userId, carId, start, expected, dailyCost);

        // تنظیم ID و مقادیر واقعی از CSV
        r->setRentalId(rentalId);
        r->setTotalCost(total);
        r->setLateFine(fine);
        r->closeRental(actual, 0); // فقط actualReturnDay رو ست می‌کنیم، جریمه رو صفر می‌گیریم چون CSV داریم

        rentals.enqueue(r);

        if (rentalId > maxId)
            maxId = rentalId;
    }

    Rental::syncNextId(maxId);

    file.close();
    cout << "✅ Rentals loaded from CSV\n";
}
