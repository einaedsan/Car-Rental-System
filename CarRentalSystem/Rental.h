#pragma once
#ifndef RENTAL_H
#define RENTAL_H

class Rental {
private:
    static int nextId;          // تولید ID خودکار
    int rentalId;
    int userId;
    int carId;
    int startDay;
    int expectedReturnDay;
    int actualReturnDay;

    double dailyCost; // هزینه روزانه
    double totalCost;
    double lateFine;  // جریمه دیرکرد

public:
    Rental(int userId, int carId, int startDay, int expectedReturnDay, double dailyCost);

    // بستن اجاره و محاسبه هزینه + جریمه
    void closeRental(int actualReturnDay, double dailyLateFine);

    // Getter ها
    int getId() const { return rentalId; }
    int getUserId() const { return userId; }
    int getCarId() const { return carId; }
    int getStartDay() const { return startDay; }
    int getExpectedReturnDay() const { return expectedReturnDay; }
    int getActualReturnDay() const { return actualReturnDay; }
    double getTotalCost() const { return totalCost; }
    double getLateFine() const { return lateFine; }
double getDailyCost() const { return dailyCost; }
    // Setter ها برای CSV
    void setRentalId(int id) { rentalId = id; }
    void setTotalCost(double cost) { totalCost = cost; }
    void setLateFine(double fine) { lateFine = fine; }

    static void syncNextId(int lastId) { nextId = lastId + 1; }
};

#endif


