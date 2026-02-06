#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

using std::string;

class Reservation {
private:
    static int nextId;
    int reservationId;
    int userId;
    int carId;
    int startDay;
    int endDay;

public:
    //Reservation();
    Reservation(int uId, int cId, int start, int end);

    int getReservationId() const;
    int getUserId() const;
    int getCarId() const;
    int getStartDay() const;
    int getEndDay() const;
    bool overlaps(int s, int e) const;
#pragma once
#ifndef RESERVATION_H
#define RESERVATION_H

#include <string>

    using std::string;

    class Reservation {
    private:
        static int nextId;
        int reservationId;
        int userId;
        int carId;
        int startDay;
        int endDay;

    public:
        Reservation(int uId, int cId, int start, int end);

        int getReservationId() const;
        int getUserId() const;
        int getCarId() const;
        int getStartDay() const;
        int getEndDay() const;
        bool overlaps(int s, int e) const;

        static void syncNextId(int lastId);
        static int getNextId();

#endif

};

#endif