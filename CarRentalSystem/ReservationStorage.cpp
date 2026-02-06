#include "ReservationStorage.h"
#include <fstream>
#include <iostream>
using namespace std;

void ReservationStorage::saveToCSV(const ReservationQueue& reservations, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "❌ Cannot open reservation file\n";
        return;
    }

    file << "reservationId,userId,carId,startDay,endDay\n";

    ReservationNode* cur = reservations.getHead();  // getter برای head باید داشته باشی
    while (cur) {
        Reservation* r = cur->data;
        file << r->getReservationId() << ","
            << r->getUserId() << ","
            << r->getCarId() << ","
            << r->getStartDay() << ","
            << r->getEndDay() << "\n";
        cur = cur->next;
    }

    file.close();
    cout << "✅ Reservations saved to CSV\n";
}

void ReservationStorage::loadFromCSV(ReservationQueue& reservations, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "⚠️ Reservation CSV not found, starting empty\n";
        return;
    }

    string line;
    getline(file, line); // skip header
    int maxId = 0;

    while (getline(file, line)) {
        int pos = 0, comma;

        // reservationId
        comma = line.find(',', pos);
        int resId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // userId
        comma = line.find(',', pos);
        int userId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // carId
        comma = line.find(',', pos);
        int carId = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // startDay
        comma = line.find(',', pos);
        int startDay = stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // endDay
        int endDay = stoi(line.substr(pos));

        // ساخت رزرو
        Reservation* r = new Reservation(userId, carId, startDay, endDay);
        r->setReservationId(resId);  // همون مقدار قبلی از CSV

        // اضافه کردن به صف
        reservations.addReservation(r);

        if (resId > maxId) maxId = resId;
    }

    // همگام سازی nextId
    Reservation::syncNextId(maxId);

    file.close();
    cout << "✅ Reservations loaded from CSV\n";
}
