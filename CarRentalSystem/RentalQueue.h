#pragma once
#pragma once
#ifndef RENTAL_QUEUE_H
#define RENTAL_QUEUE_H

#include "RentalQueueNode.h"

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
};

#endif
