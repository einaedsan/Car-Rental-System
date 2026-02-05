#pragma once
#ifndef CAR_LIST_H
#define CAR_LIST_H

#include "CarNode.h"

class CarList {
private:
    CarNode* head;
    CarNode* tail;

public:
    CarList();

    void pushBack(Car* car);
    Car* findById(int carId);
    CarNode* getHead() const;
};

#endif
