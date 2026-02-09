#pragma once
#ifndef RESERVATION_PRIORITY_QUEUE_H
#define RESERVATION_PRIORITY_QUEUE_H

#include "Reservation.h"

class ReservationPriorityQueue {
private:
    Reservation** heap;
    int size;
    int capacity;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize();

public:
    ReservationPriorityQueue(int cap = 10);
    ~ReservationPriorityQueue();

    bool addReservation(Reservation* r);
    Reservation* popNext();

    bool hasConflict(int startDay, int endDay) const;
    bool isEmpty() const;

    int getSize() const { return size; }
    Reservation* getAt(int index) const { return heap[index]; } // برای CSV
};

#endif
