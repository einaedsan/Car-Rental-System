#pragma once
#ifndef RESERVATION_STORAGE_H
#define RESERVATION_STORAGE_H

#include <string>
#include "ReservationQueue.h"

class ReservationStorage {
public:
    // ذخیره‌ی صف رزروها در یک فایل CSV
    static void saveToCSV(const ReservationQueue& reservations, const std::string& filename);

    // بارگذاری صف رزروها از یک فایل CSV
    static void loadFromCSV(ReservationQueue& reservations, const std::string& filename);
};

#endif
