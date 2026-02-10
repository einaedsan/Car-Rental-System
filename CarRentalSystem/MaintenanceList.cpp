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
bool  MaintenanceList::hasPendingMaintenance() const {
    MaintenanceNode* cur = head;
    while (cur) {
        // فرض کن هر Maintenance که وجود داره یعنی منتظر است
        return true;  // اگر میخوای جزئیات دقیق‌تر، می‌تونی یک flag تو Maintenance اضافه کنی
        cur = cur->next;
    }
    return false;
}