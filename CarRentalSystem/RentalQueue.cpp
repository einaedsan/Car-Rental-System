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
    return nullptr; // پ?دا نشد
}
void RentalQueue::showActiveRentals() const {
    RentalQueueNode* cur = front;
    bool found = false;

    while (cur) {
        Rental* r = cur->rental;
        if (r->isActive()) {
            cout << "Rental ID: " << r->getId()
                << " | User ID: " << r->getUserId()
                << " | Car ID: " << r->getCarId()
                << " | From day " << r->getStartDay()
                << " to " << r->getExpectedReturnDay() << "\n";
            found = true;
        }
        cur = cur->next;
    }

    if (!found)
        cout << "No active rentals.\n";
}

double RentalQueue::calculateTotalIncome() const {
    double total = 0;

    RentalQueueNode* cur = front;

    while (cur) {
        Rental* r = cur->rental;

        // فقط اجاره‌های بسته شده حساب شوند
        if (!r->isActive()) {
            total += r->getTotalCost();
        }

        cur = cur->next;
    }

    return total;
}

