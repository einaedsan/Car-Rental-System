#include "AVLTree.h"
#include "Car.h"

AVLTree::AVLTree() : root(NULL) {}

int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right)
        ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right)
        ? height(x->left) : height(x->right));

    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right)
        ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right)
        ? height(y->left) : height(y->right));

    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, int key, Car* value) {
    if (!node)
        return new AVLNode(key, value);

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else
        return node;

    node->height = 1 + (height(node->left) > height(node->right)
        ? height(node->left) : height(node->right));

    int balance = balanceFactor(node);

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(int key, Car* value) {
    root = insert(root, key, value);
}

Car* AVLTree::search(AVLNode* node, int key) const {
    if (!node) return NULL;
    if (key == node->key) return node->value;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

Car* AVLTree::search(int key) const {
    return search(root, key);
}
