#include "RentalQueue.h"

RentalQueue::RentalQueue() : front(nullptr), rear(nullptr) {}

bool RentalQueue::isEmpty() const { return front == nullptr; }

void RentalQueue::enqueue(Rental* rental) {
    RentalQueueNode* node = new RentalQueueNode(rental);
    if (!rear) {
        front = rear = node;
    }
    else {
        rear->next = node;
        rear = node;
    }
}

void RentalQueue::dequeue() {
    if (!front) return;
    RentalQueueNode* temp = front;
    front = front->next;
    if (!front) rear = nullptr;
    delete temp;
}

Rental* RentalQueue::peek() const {
    return front ? front->rental : nullptr;
}


Rental* RentalQueue::findById(int rentalId) const {
    RentalQueueNode* cur = front;
    while (cur) {
        if (cur->rental->getId() == rentalId)
            return cur->rental;
        cur = cur->next;
    }
    return nullptr;
}

Rental* RentalQueue::findByCarId(int carId) const {
    RentalQueueNode* cur = front;
    while (cur) {
        if (cur->rental->getCarId() == carId)
            return cur->rental;
        cur = cur->next;
    }
    return nullptr; // Å?œ« ‰‘œ
}
