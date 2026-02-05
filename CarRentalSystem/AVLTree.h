#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AVLNode.h"

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) const;
    int balanceFactor(AVLNode* node) const;

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insert(AVLNode* node, int key, Car* value);
    Car* search(AVLNode* node, int key) const;

public:
    AVLTree();

    void insert(int key, Car* value);
    Car* search(int key) const;
};

#endif

