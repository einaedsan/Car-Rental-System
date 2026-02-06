#include "ManagerMenu.h"
using namespace std;

void ManagerMenu::show() {
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Manager Menu ===\n";
        cout << "1. Revenue and Performance Report\n";
        cout << "2. Manage Problematic Users\n";
        cout << "0. Logout\n";
        cout << "Select option: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "[Placeholder] Generate revenue and performance report...\n";
            break;
        case 2:
            cout << "[Placeholder] Block or manage problematic users...\n";
            break;
        case 0:
            exitMenu = true;
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    }
}
