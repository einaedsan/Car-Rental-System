#pragma once
#ifndef RENTAL_STORAGE_H
#define RENTAL_STORAGE_H

#include <string>
#include "RentalQueue.h"

class RentalStorage {
public:
    // ذخیره‌ی صف اجاره‌ها در فایل CSV
    static void saveToCSV(const RentalQueue& rentals, const std::string& filename);

    // بارگذاری صف اجاره‌ها از فایل CSV
    static void loadFromCSV(RentalQueue& rentals, const std::string& filename);
};

#endif
