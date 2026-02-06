#pragma once
#ifndef FLEET_STORAGE_H
#define FLEET_STORAGE_H

#include "Fleet.h"
#include <string>

using std::string;

class FleetStorage {
public:
    static void saveCars(const Fleet& fleet, const string& filename);
    static void loadCars(Fleet& fleet, const string& filename);
};

#endif

