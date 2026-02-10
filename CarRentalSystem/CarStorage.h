#pragma once
#pragma once
#include "CarList.h"
#include <string>

class CarStorage {
public:
    static void saveToCSV(const CarList& cars, const std::string& filename);
    static void loadFromCSV(CarList& cars, const std::string& filename);
};
