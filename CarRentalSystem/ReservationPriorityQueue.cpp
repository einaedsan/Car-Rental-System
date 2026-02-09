#include "ReservationPriorityQueue.h"
#include <iostream>

ReservationPriorityQueue::ReservationPriorityQueue(int cap)
    : size(0), capacity(cap) {
    heap = new Reservation * [capacity];
}

ReservationPriorityQueue::~ReservationPriorityQueue() {
    delete[] heap;
}

void ReservationPriorityQueue::resize() {
    capacity *= 2;
    Reservation** newHeap = new Reservation * [capacity];
    for (int i = 0; i < size; i++)
        newHeap[i] = heap[i];
    delete[] heap;
    heap = newHeap;
}

void ReservationPriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[parent]->getStartDay() <= heap[index]->getStartDay())
            break;

        std::swap(heap[parent], heap[index]);
        index = parent;
    }
}

void ReservationPriorityQueue::heapifyDown(int index) {
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < size &&
            heap[left]->getStartDay() < heap[smallest]->getStartDay())
            smallest = left;

        if (right < size &&
            heap[right]->getStartDay() < heap[smallest]->getStartDay())
            smallest = right;

        if (smallest == index) break;

        std::swap(heap[index], heap[smallest]);
        index = smallest;
    }
}

bool ReservationPriorityQueue::hasConflict(int start, int end) const {
    for (int i = 0; i < size; i++) {
        if (heap[i]->overlaps(start, end))
            return true;
    }
    return false;
}

bool ReservationPriorityQueue::addReservation(Reservation* r) {
    if (hasConflict(r->getStartDay(), r->getEndDay()))
        return false;

    if (size == capacity)
        resize();

    heap[size] = r;
    heapifyUp(size);
    size++;
    return true;
}

Reservation* ReservationPriorityQueue::popNext() {
    if (size == 0) return NULL;

    Reservation* min = heap[0];
    heap[0] = heap[size - 1];
    size--;
    heapifyDown(0);
    return min;
}

bool ReservationPriorityQueue::isEmpty() const {
    return size == 0;
}
