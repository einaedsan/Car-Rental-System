#pragma once
#pragma once
#ifndef RENTAL_QUEUE_H
#define RENTAL_QUEUE_H

#include "RentalQueueNode.h"
#include<iostream>
using namespace std;
class RentalQueue {
private:
    RentalQueueNode* front;
    RentalQueueNode* rear;

public:
    RentalQueue();

    bool isEmpty() const;

    void enqueue(Rental* rental);   // اضافه کردن Rental به صف
    void dequeue();                  // حذف اولین Rental
    Rental* peek() const;            // دیدن اولین Rental
    RentalQueueNode* frontNode() const { return front; } // getter برای CSV و ذخیره/بارگذاری

    Rental* findById(int rentalId) const;
    Rental* findByCarId(int carId) const;
    void showActiveRentals() const;
    double calculateTotalIncome() const;

    
};

#endif
