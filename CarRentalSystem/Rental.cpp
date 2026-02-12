#include "Rental.h"

int Rental::nextId = 1;

Rental::Rental(int uId, int cId, int start, int expected, double costPerDay)
    : rentalId(nextId++), userId(uId), carId(cId), startDay(start),
    expectedReturnDay(expected), actualReturnDay(0), dailyCost(costPerDay),
    totalCost(0), lateFine(0) {
}
void Rental::closeRental() {
    actualReturnDay = SystemDate::getDay();  // روز واقعی سیستم
    int daysRented = actualReturnDay - startDay;
    if (daysRented < 1) daysRented = 1;

    totalCost = daysRented * dailyCost;

    if (actualReturnDay > expectedReturnDay) {
        lateFine = (actualReturnDay - expectedReturnDay) * SystemConfig::DAILY_LATE_FINE;
        totalCost += lateFine;
    }
    else {
        lateFine = 0;
    }
}
void Rental::extendRental(int extraDays) {
    if (extraDays > 0)
        expectedReturnDay += extraDays;
}


bool Rental:: isActive() const {
    return actualReturnDay == 0;   // یعنی هنوز تحویل داده نشده
}

void  Rental::setActualReturnDay(int day) {
    actualReturnDay = day;
}
