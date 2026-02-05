#include "CarList.h"
#include "Car.h"

CarList::CarList() : head(NULL), tail(NULL) {}

void CarList::pushBack(Car* car) {
    CarNode* node = new CarNode(car);

    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

Car* CarList::findById(int carId) {
    CarNode* cur = head;
    while (cur) {
        if (cur->data->getId() == carId)
            return cur->data;
        cur = cur->next;
    }
    return NULL;
}

CarNode* CarList::getHead() const {
    return head;
}
