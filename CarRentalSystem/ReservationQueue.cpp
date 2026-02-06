#include "ReservationQueue.h"

ReservationQueue::ReservationQueue() : head(NULL) {}

bool ReservationQueue::hasConflict(int start, int end) const {
    ReservationNode* cur = head;
    while (cur) {
        if (cur->data->overlaps(start, end))
            return true;
        cur = cur->next;
    }
    return false;
}

bool ReservationQueue::addReservation(Reservation* r) {
    if (hasConflict(r->getStartDay(), r->getEndDay()))
        return false;

    ReservationNode* node = new ReservationNode(r);

    if (!head || r->getStartDay() < head->data->getStartDay()) {
        node->next = head;
        head = node;
        return true;
    }

    ReservationNode* cur = head;
    while (cur->next &&
        cur->next->data->getStartDay() <= r->getStartDay()) {
        cur = cur->next;
    }

    node->next = cur->next;
    cur->next = node;
    return true;
}

Reservation* ReservationQueue::popNext() {
    if (!head) return NULL;

    ReservationNode* temp = head;
    head = head->next;

    Reservation* r = temp->data;
    delete temp;
    return r;
}

bool ReservationQueue::isEmpty() const {
    return head == NULL;
}
ReservationNode* ReservationQueue::getHead() const { return head; }