#include "Rental.h"

int Rental::nextId = 1;

Rental::Rental(int uId, int cId, int start, int expected)
    : rentalId(nextId++),
    userId(uid),
    carId(cid),
    startDay(start),
    expectedReturnDay(expected),
    actualReturnDay(0),
    totalCost(0),
    lateFine(0) {
}

int Rental::getId() const {
    return rentalId;
}

int Rental::getUserId() const {
    return userId;
}

int Rental::getCarId() const {
    return carId;
}

int Rental::getStartDay() const {
    return startDay;
}

int Rental::getExpectedReturnDay() const {
    return expectedReturnDay;
}

int Rental::getActualReturnDay() const {
    return actualReturnDay;
}

double Rental::getTotalCost() const {
    return totalCost;
}

double Rental::getLateFine() const {
    return lateFine;
}

void Rental::closeRental(int actual, double dailyFine) {
    actualReturnDay = actual;

    if (actualReturnDay > expectedReturnDay) {
        lateFine = (actualReturnDay - expectedReturnDay) * dailyFine;
    }
}