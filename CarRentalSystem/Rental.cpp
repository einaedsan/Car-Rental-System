#include "Rental.h"

int Rental::nextId = 1;

Rental::Rental(int uId, int cId, int start, int expected, double costPerDay)
    : rentalId(nextId++), userId(uId), carId(cId), startDay(start),
    expectedReturnDay(expected), actualReturnDay(0), dailyCost(costPerDay),
    totalCost(0), lateFine(0) {
}

void Rental::closeRental(int actual, double dailyLateFine) {
    actualReturnDay = actual;

    int daysRented = expectedReturnDay - startDay;
    totalCost = daysRented * dailyCost;

    if (actualReturnDay > expectedReturnDay) {
        lateFine = (actualReturnDay - expectedReturnDay) * dailyLateFine;
        totalCost += lateFine;
    }
    else {
        lateFine = 0;
    }
}
