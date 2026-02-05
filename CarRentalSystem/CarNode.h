#pragma once
#ifndef CAR_NODE_H
#define CAR_NODE_H

class Car;

struct CarNode {
    Car* data;
    CarNode* prev;
    CarNode* next;

    CarNode(Car* car): data(car), prev(NULL), next(NULL) {}
};

#endif
