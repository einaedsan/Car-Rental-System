#include "MaintenanceList.h"

MaintenanceList::MaintenanceList() : head(NULL), tail(NULL) {}

void MaintenanceList::addMaintenance(Maintenance* m) {
    MaintenanceNode* node = new MaintenanceNode(m);

    if (!head) {
        head = tail = node;
    }
    else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

MaintenanceNode* MaintenanceList::getHead() const {
    return head;
}
