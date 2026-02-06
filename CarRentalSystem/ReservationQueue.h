#pragma once
#ifndef RESERVATION_QUEUE_H
#define RESERVATION_QUEUE_H

#include "Reservation.h"

struct ReservationNode {
    Reservation* data;
    ReservationNode* next;

    ReservationNode(Reservation* r)
        : data(r), next(NULL) {
    }
};

class ReservationQueue {
private:
    ReservationNode* head;

public:
    ReservationQueue();

    bool addReservation(Reservation* r);
    Reservation* popNext();
    bool hasConflict(int startDay, int endDay) const;
    bool isEmpty() const;
    ReservationNode* getHead() const { return head; }

};

#endif

