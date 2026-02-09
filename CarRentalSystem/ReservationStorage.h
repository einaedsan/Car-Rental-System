#pragma once
#ifndef RESERVATION_STORAGE_H
#define RESERVATION_STORAGE_H

#include "ReservationPriorityQueue.h"
#include <string>

class ReservationStorage {
public:
    static void saveToCSV(const ReservationPriorityQueue& pq, const std::string& filename);
    static void loadFromCSV(ReservationPriorityQueue& pq, const std::string& filename);
};

#endif
