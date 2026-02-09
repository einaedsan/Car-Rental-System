#include "ReservationStorage.h"
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

void ReservationStorage::saveToCSV(const ReservationPriorityQueue& pq, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open())
        return;

    file << "reservationId,userId,carId,startDay,endDay\n";

    for (int i = 0; i < pq.getSize(); i++) {
        Reservation* r = pq.getAt(i);
        file << r->getReservationId() << ","
            << r->getUserId() << ","
            << r->getCarId() << ","
            << r->getStartDay() << ","
            << r->getEndDay() << "\n";
    }

    file.close();
}

void ReservationStorage::loadFromCSV(ReservationPriorityQueue& pq, const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open())
        return;

    string line;
    getline(file, line); // رد کردن هدر

    int maxId = 0;

    while (getline(file, line)) {
        int pos = 0;
        int comma;

        // reservationId
        comma = line.find(',', pos);
        int resId = std::stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // userId
        comma = line.find(',', pos);
        int userId = std::stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // carId
        comma = line.find(',', pos);
        int carId = std::stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // startDay
        comma = line.find(',', pos);
        int startDay = std::stoi(line.substr(pos, comma - pos));
        pos = comma + 1;

        // endDay
        int endDay = std::stoi(line.substr(pos));

        Reservation* r = new Reservation(userId, carId, startDay, endDay);
        r->setReservationId(resId);

        pq.addReservation(r);

        if (resId > maxId)
            maxId = resId;
    }

    Reservation::syncNextId(maxId);
    file.close();
}
