#pragma once
#ifndef MAINTENANCE_LIST_H
#define MAINTENANCE_LIST_H

#include "Maintenance.h"

struct MaintenanceNode {
    Maintenance* data;
    MaintenanceNode* prev;
    MaintenanceNode* next;

    MaintenanceNode(Maintenance* m)
        : data(m), prev(NULL), next(NULL) {
    }
};

class MaintenanceList {
private:
    MaintenanceNode* head;
    MaintenanceNode* tail;

public:
    MaintenanceList();

    void addMaintenance(Maintenance* m);
    MaintenanceNode* getHead() const;
    bool hasPendingMaintenance() const;
};

#endif
