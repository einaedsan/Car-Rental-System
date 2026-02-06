#pragma once
#ifndef MAINTENANCE_STORAGE_H
#define MAINTENANCE_STORAGE_H

#include "MaintenanceList.h"
#include <string>

using std::string;

class MaintenanceStorage {
public:
    static void save(const MaintenanceList& list, const string& filename);
    static void load(MaintenanceList& list, const string& filename);
};

#endif

