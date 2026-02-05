#include "Reservation.h"

int Reservation::nextId = 1;

//Reservation::Reservation(): reservationId(0), userId(0), carId(0),startDay(0), endDay(0) {
//}

Reservation::Reservation(int uId, int cId, int start, int end): reservationId(nextId++), userId(uId), carId(cId),startDay(start), endDay(end) {
}

int Reservation::getReservationId() const {
    return reservationId;
}

int Reservation::getUserId() const {
    return userId; 
}

int Reservation::getCarId() const { 
    return carId;
}

int Reservation::getStartDay() const { 
    return startDay; 
}

int Reservation::getEndDay() const {
    return endDay;
}

bool Reservation::overlaps(int s, int e) const {
    return !(e <= startDay || s >= endDay);
}