#pragma once
#ifndef RENTAL_H
#define RENTAL_H

class Rental {
private:
    static int nextId;
    int rentalId;
    int userId;
    int carId;
    int startDay;
    int expectedReturnDay;
    int actualReturnDay;
    double totalCost;
    double lateFine;

public:
    Rental(int userId, int carId, int startDay, int expectedReturnDay);

    int getId() const;
    int getUserId() const;
    int getCarId() const;
    int getStartDay() const;
    int getExpectedReturnDay() const;
    int getActualReturnDay() const;
    double getTotalCost() const;
    double getLateFine() const;
    void closeRental(int actualReturnDay, double dailyFine);
};

#endif