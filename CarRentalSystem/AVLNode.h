#pragma once
#ifndef AVL_NODE_H
#define AVL_NODE_H
#include "Car.h"

class Car;

struct AVLNode {
    int key;        
    Car* value;     

    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, Car* v)
        : key(k), value(v),
        left(NULL), right(NULL),
        height(1) {
    }
};

#endif

